fn takes_ownership(some_string:&String){
    println!("{}", some_string);
}

fn makes_copy(some_integer:i32){
    println!("{}", some_integer);
}

fn main() {
    let s = String::from("hello");

    takes_ownership(&s);

    let e = &s;
    println!("{}", e);

    let x = 5;
    makes_copy(x);
}
