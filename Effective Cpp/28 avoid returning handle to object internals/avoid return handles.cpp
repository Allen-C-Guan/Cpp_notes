//
// Created by Allen on 2021/7/4.
//

#include <iostream>
#include <string>
#include <memory>
#include <vector>

/*
 * ************ 28.避免返回handle指向对象内部成分 *******************
 * 什么是handle！
 * handle指的就是reference，pointer，iterator等。他们之所以可以称之为handle，因为他们本质上没有意义，
 * 只是某个对象的抓手而已。那么既然是个抓手，很有可能这个抓手下面有对象，也有可能没有对象，真的就只是一个抓手
 *
 * 为何要避免返回handle指向对象的内部？
 * 1. 返回handle会导致封装性变差!
 *  比如：你用public成员函数返回一个private成员函数。这就导致这private实际上就是public的了
 *  再比如：你返回一个非const引用（但是实际上这个函数是const的,你通过指针获取了人家私有的成员），
 *  这会导致内部变量会被修改。
 *
 * 2. handle只要被返回出去，就有比其所指对象更长寿的风险！！
 *  也就是说，一旦你把handle返回了出去，那么该handle的生命周期完全是用户来决定的，这就会导致handle和
 *  object的生命周期的不一致！！
 *
 *  这种事情通常会发生在，object不是自己专有的member的情况下，也就是说你返回的并不是你自己独有的member，
 *  而是你引用或者指针赋值过来的别人的obj，只是挂在你这里了而已的情况下。
 *  而对于你自己独有的member 通常情况下，成员函数返回reference还是安全的，因为member不在了，obj一定
 *  不在了，其二者声明周期一定是一致的，只有可以调用该成员函数，该member就一定是存在的！！
 *
 */




int main()
{

}