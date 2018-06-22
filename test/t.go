package main

import "time"
import "fmt"

func A() int {
    a := 10
    return a
}

func B() int {
    return  20 + A()
}

func C() int {
    return 30 + B()
}

func main() {
    time.Sleep(10 * time.Second);
    r := C()
    fmt.Println(r)
}
