/*
 编译的工作方式
 编译器如何将所有source code编译和链接起来的？
 1. include的范围：在使用pre-process的 #include 的时候，编译器会在该范围内的所有head file里面，搜索到相应的head file，并将其粘贴到对应位置
 2. linking的范围： 即编译器linking的范围，当一个变量或者函数被声明以后，在call的时候编译器的linker会根据名称
    和signature在linking的范围中，寻找该声明对应的defination。 而后根据defination，运行程序。
 
 
 Library的结构：
 1. include: 该文件夹下存放的是head file。 即所有变量以及函数等的decleration.
 2. lib: 该文件是 definiation 的 binary code。
 
 library 文件类型与名称：
 1. ~.dll是dynamic library：dynamic library的linking发生在run，即project被launch之后，在project运行的过程中，
    一旦需要dynamic library的内容， dynamic library中的相应内容会被load到内存中，而后才被执行。
 
 2. ~.lib是static library： static lib的link发生在compile time的时候，即 将cpp file 相互独立的compile 到 obj file之后， linker将所有obj内容串联起来，相互调用。
 
 3. ~dll.lib是记录dynamic library中所有symbol和function的位置的static library，其作用类似于一个以static library形式存储的pointer，该pointer可以链接dynamic library. 如果没有该文件，dynamic lib也可以使用，但是
    需要在每次被调用的时候，都对dynamic lib进行查找，找的符合条件的函数，然后使用。
 
 
 
 
 使用static linking的方法主要分成两步：
 1. 对编译器 include 范围的扩充： 将library下的include的文件夹扩充到 include 的范围中
 2. 对编译器linker范围的扩充： 将library中的lib文件夹，扩充到 linker的范围中，
    并将~.lib文件名加入到input下的dependencies中
 
 
 
 
 
            *** dynamic linking *****
 通常情况下， library的head file是既支持dynamic Linking 也支持 static linking 的。因此，同样的head file可以既可以使用dll，
 也可以使用lib。
 
 方法1: 用～dll.lib来实现dynamic library的调用。
    原理： ~dll.lib是一些记录.dll中symbol和function 位置的pointer们。
    操作：1. 对include范围扩充： 采用和static linking完全相同的方法
         2. 对linker的范围扩充： 将library中的lib文件夹，扩充到 linker的范围中，并将~dll.lib文件名加入到input下的dependencies中。
         3. 移动.dll文件：将.dll文件放置到与exe文件相同的文件夹中。
 
 
 */
