# include <iostream>
using namespace std;

//void Log2(const char* message);

// head的作用就是复制粘贴！！！！ 除此之外别无他用！采用的方式就是 # include



/*
 declearation
 
 declearation的作用就是，告诉linking，Log2一定存在于其他文件的某处， 你去给我找去。找的时候会依据 函数名+signature来找
 如果你没找到，那也会报错，报错的内容是你没有定义该函数。
 
 因此，只要不是在当前file下定义的内容，你就一定要声明这东西一定存在于这个project的某处，不然你就不能用。
 
 
 
 
 head的作用（和import相似）

 可是时候问题就来了，如果我们在这个project里面，随时都要用到这个log2的函数，那么难道我每次都要写这句话么？那如果我有100个function，难道每次都这们写100句declearation么
 
 于是就有了head！
 head的作用就是复制粘贴，你写啥他就粘贴啥，就很简单，因此我们可以把100句的declearation都放在head里面，一句include，就解决问题了。
 这时候，所有的declearation就被复制粘贴到此处了。
 
 这里我们用一句# include log.h就把log.h里全部的内容都复制粘贴过来了
 */

/*
  #的作用
 #表示，所有的内容都是被preprocess的
 # pragma once在这里就会体现了， common.h的include导致log.h中的内容在这里被复制了2次， student也被define了两次。
 可是由于pragma once的作用，让preprocess的时候，log.h中的全部内容，在一个file里只能出现一次的缘故， common.h并没有在preprocess
的过程中真的被复制过来。
 
 */

# include "Log.h"
# include "common.h"

/*
 include 为何有时候用<>有时候用“”
 
 这是因为“”表示当前路径下的文件，而<>表示搜索系统+附加包含路径中的文件。简单理解可以为<>范围更大，支持第三方库的搜索。 “”通常是自己的内容。
 */


void head_test(){
    cout << "Hello Word!" << endl;
    Log2("this is a Log function");
}
