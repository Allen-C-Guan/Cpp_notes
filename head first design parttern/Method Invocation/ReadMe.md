# 指令模式
命令模式将"请求"封装成对象，以便使用不同的请求，队列或者日志来参数化其他对象。命令模式也支持可撤销操作。
## 指令模式的要点
1. commend
    1. 以"拥有"的方式，将执行者（door)和当前指令(OpenDoorCmd)绑定到一起
    2. commend 要提供执行接口(execute()， 执行方式为调用执行者来执行)供invoker使用. 
    commend只暴露一个execute给invoker来使用
2. invoker
    1. invoker（remoteController）要接收commend（setCommend())
    2. 给出执行时机（pressedButton)
3. 接收者（执行者）
    1. 将执行动作封装一个接口，提供给commend来使用
    
这样，invoker一旦获取到了commend，在invoker想要执行的时候，通过调用commend.execute()接口
就可以执行相应的动作，invoker不需要感知谁来执行，也不需要感知如何执行。

但实际上，execute()通过调用cmd所持有的执行者(reciever)来执行的，执行细节被reciever封装在了其内部。

通过以上的流程我们发现，invoker不需要知道实现细节，变成了一个莫得感情的透传机器，他的全部工作就是接收
commend，执行commend，传的是啥invoker自己也不知道，只知道这个东西可以被execute就够了。
而实现都是由执行者封装在了内部。

## 优点
1. 灵活性
invoker由于只是莫得感情的执行机器，他才不在乎自己掌握的commend是什么呢！比如最开始这个invoker
手握的commend只是开门的命令，你也可以将其更换为核弹发射的命令，对于invoker而言，这两个命令没有任何区别，
因为invoker感知的只有cmd的execute接口，两者都提供了这个接口，那么invoker执行的方式没有任何区别！
