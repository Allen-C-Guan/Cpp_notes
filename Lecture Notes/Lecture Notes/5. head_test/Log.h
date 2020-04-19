//# pragma once
/*
 pragma once的作用就是防止该内容被重复复制到其他里面，这个里面的所有内容，在一个file里，最多只能存在一次！！！
 */

//下面这个方法也可以，这是一个比较古老的方法 效果和pragma once相同
#ifndef _LOG_H //如果没有define _LOG_H
#define _LOG_H //那就define一个，否则就不定义

void Log2(const char* message);
struct student {};

#endif

/*
 当这些语句被复制到其他file的时候，只有第一个define里面的内容才生效，后面的就不生效了，因为ifndef判定为false
 */
