use std::ops::Deref;

struct MyBox<T>(T);

impl<T> MyBox<T> {
    fn new(x:T)->MyBox<T>{
        MyBox(x)
    }
}

impl<T> Deref for MyBox<T>{
    //特殊的类型关联
    type Target = T;
    fn deref(&self) -> &T{
        //元组的第一个元素
        &self.0
    }
}

fn main() {
    println!("Hello, world!");
    let x = 5;
    let y = MyBox::new(x);

    assert_eq!(5, x);
    assert_eq!(5, *y);
    //*y ==> *(y.deref())
}
