--[[--

Creating a copy of an table with fully replicated properties.

**Usage:**

    -- Creating a reference of an table:
    local t1 = {a = 1, b = 2}
    local t2 = t1
    t2.b = 3    -- t1 = {a = 1, b = 3} <-- t1.b changed

    -- Createing a copy of an table:
    local t1 = {a = 1, b = 2}
    local t2 = clone(t1)
    t2.b = 3    -- t1 = {a = 1, b = 2} <-- t1.b no change


@param mixed object
@return mixed

]]
function clone(object, setMetaTable)
    local lookup_table = {}
    local function _copy(object)
        if type(object) ~= "table" then
            return object
        elseif lookup_table[object] then
            return lookup_table[object]
        end
        local new_table = {}
        lookup_table[object] = new_table
        for key, value in pairs(object) do
            new_table[_copy(key)] = _copy(value)
        end
        if setMetaTable == false then
            return new_table
        end
        return setmetatable(new_table, getmetatable(object))
    end
    return _copy(object)
end


function protoClone(object)
    local lookup_table = {}
    local function _copy(object)
        if type(object) ~= "table" then
            return object
        elseif lookup_table[object] then
            return lookup_table[object]
        end
        local new_table = {}
        lookup_table[object] = new_table
        for key, value in pairs(object) do
            new_table[_copy(key)] = _copy(value)
        end
        return new_table
    end
    return _copy(object)
end

local objectCount = 0
local function getObjectCount()
    objectCount = objectCount + 1
    return objectCount
end


function instanceOf(cls)
    if cls and type(cls) == 'table' and cls.__cname then
        return cls.__cname
    end
    return NONE_CLASS
end

function iskindof(obj, className)
    local t = type(obj)

    if t == "table" then
        local mt = getmetatable(obj)
        while mt and mt.__index do
            if mt.__index.__cname == className then
                return true
            end
            mt = mt.super
        end
        return false

    elseif t == "userdata" then

    else
        return false
    end
end

function LuaExtend(src, ...)
	local meta = getmetatable(src)
	local parents = {...}
	local newParents = {}

	for k,v in pairs(parents) do
		table.insert(newParents, v:new())
	end

	setmetatable(src, {
		__index = function (table, key)
			local find = meta[key]
			if find then
				return find
			end

			for k,v in pairs(newParents) do
				find = v[key]
				if find then
					return find
				end
			end
		end
	})
end


--[[
    this is a class like OO language
    
]]
function class(classname, super)
    local superType = type(super)
    local cls

    if super then
        cls = setmetatable({}, {__index = super})
        cls.super = super
    else
        cls = {ctor = function() end, _define = function() end}
    end

    cls.__cname = classname

    cls.ObscureInt = function(self, keyList)
        self.ObscureKeyList = keyList
        self.ObscureRealList = {}
        self.ObscureList = {}
    end

    local func               
    cls.__newindex = function(o, k, v)
        func = cls['set__' .. k]
        if func then 
            func(o, v)
        else 
            -- if (k == "hp") then
            --     logError("设置HP键值")
            -- end
            if rawget(o, "ObscureKeyList") and rawget(o, "ObscureKeyList")[k] ~= nil then
                local v = v or 0
                v = math.floor(v)
                rawget(o, "ObscureRealList")[k] = v
                -- logWarn("加密键值:" .. k)
                -- logWarn("加密之前的原值:" .. v)
                local curKey = rawget(o, "ObscureKeyList")[k]
                -- logWarn("加密key:" .. curKey)
                --rawset(o, k, v ~ curKey)
                rawget(o, "ObscureList")[k] = v ~ curKey
                -- logWarn("加密之后的新值:" .. (v ~ curKey))
                -- logWarn("加密之后的ObscureRealList值:" .. rawget(o, "ObscureRealList")[k])
                return
            end
            rawset(o, k, v) 
        end
    end
    cls.__index = function(o, k)
        func = cls['get__' .. k]
        if func then return func(o, k) end
        if rawget(o, "ObscureKeyList") and rawget(o, "ObscureKeyList")[k] ~= nil then
            local realValue = rawget(o, "ObscureRealList")[k]
            if realValue ~= nil then
                --local curATK = rawget(o, k)
                local curATK = rawget(o, "ObscureList")[k]
                -- logWarn("解密键值:" .. k)
                -- logWarn("解密之前的原值:" .. curATK)
                -- logWarn("解密之前的真实值:" .. rawget(o, "ObscureRealList")[k])
                -- logWarn("解密之后的值:" .. (curATK ~ rawget(o, "ObscureKeyList")[k]))
                local calcValue = (curATK ~ rawget(o, "ObscureKeyList")[k])
                if (realValue ~= calcValue) then
                    logError("有人修改了内存")
                end
                return calcValue
            end
        end
        if cls[k] then return cls[k] end
        return rawget(o, k)
    end

    function cls:new(...)
        local instance = setmetatable({}, cls)
        instance.id = getObjectCount()
        instance.class = cls   

        local funcs = {}
        local super = cls 
        while super do 
            if super.super == nil or super._define ~= super.super._define then super._define(instance, ...) end
            if super.super == nil or super.ctor ~= super.super.ctor then table.insert(funcs, 1, super.ctor) end
            super = super.super
        end
        for i = 1, #funcs do 
            funcs[i](instance, ...)
        end
        return instance
    end

    function cls:create(...)
        return self:new(...)
    end

    function cls:isClass(classObj)
        local cls = self.class
        while cls do 
            if cls == classObj then return true end
            cls = cls.super
        end
        return false
    end 
    return cls
end

Component = CLASS