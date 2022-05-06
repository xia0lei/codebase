use trait_test::Summary;
use trait_test::Tweet;

fn main() {
    let tweet = Tweet{
        username:String::from("horse_ebooks"),
        content:String::from("of course, as you probably already know, people"),
        reply:false,
        retweet:false
    };
    println!("new tweet:{}", tweet.summarize());
}
