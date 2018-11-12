# “自顶向下，逐步求精”洗衣机程序设计
## 什么是自顶向下，逐步求精?
>指的是程序设计时，应先考虑总体，后考虑细节；先考虑全局目标，后考虑局部目标。不要一开始就过多追求众多的细节，先从最上层总目标开始设计，逐步使问题具体化。对复杂问题，应设计一些子目标作为过渡，逐步细化。

仔细观察您洗衣机的运作过程，运用Top-down设计方法和Pseudocode 描述洗衣机控制程序。假设洗衣机可执行的基本操作如下：<br>

    water_in_switch(open_close) // open 打开上水开关，close关闭
    water_out_switch(open_close) // open 打开排水开关，close关闭
    get_water_volume() //返回洗衣机内部水的高度
    motor_run(direction) // 电机转动。left左转，right右转，stop停
    time_counter() // 返回当前时间计数，以秒为单位
    halt(returncode) //停机，success 成功 failure 失败
## 洗衣机案例
1）请使用伪代码分解“正常洗衣”程序的大步骤。包括注水、浸泡等<br>

1. 模式选取
2. 注水
3. 计算水
4. 浸泡
5. 转动
6. 脱水/排水
7. 再转动
8. 结束

2）进一步用基本操作、控制语句（IF、FOR、WHILE等）、变量与表达式，写出每
个步骤的伪代码<br>

    READ 用户洗衣模式 
    READ 注水量 
    SET water to 0 
    FUNCTION wateropen(注水量) 
    { 
        WHILE (water < 注水量) 
    { 
        Water 计水 
    } 
    }    
        FUNCTION dip(用户洗衣模式) 
    { 
        IF(用户洗衣模式==浸泡){ 
        SET timer to 0 
        WHILE (timer < 浸泡时间) 
    { 
        停止运行 
        Timer 计时 
    } 
    }

    }   
        开始洗衣 
    FUNCTION begin(洗衣时间) 
    { 
        SET timer to 0 
        WHILE(timer < 洗衣时间) 
    {   
        滚筒左三次右三次 
        Timer 计时 
    } 
    } 
    FUNCTION waterout(水量) 
    { 
        WHILE(water > 0) 
    { 
        排水 
        Water 计水 
    } 
    } 
        FUNCTION dry(脱水时间) 
    { 
        SET timer to 0 
        WHILE(timer＜脱水时间) 
    {   
        脱水 
        Timer 计时 
    } 
    } 

