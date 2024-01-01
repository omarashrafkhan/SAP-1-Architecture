from machine import Pin
import utime

accmux = Pin(12,Pin.OUT)
reset = Pin(5,Pin.OUT)
pcload = Pin(28,Pin.OUT)
#for alu
add_sub = Pin(16,Pin.OUT)
A3 =Pin(8,Pin.OUT)
A2 =Pin(9,Pin.OUT)
A1 =Pin(10,Pin.OUT)
A0 =Pin(11,Pin.OUT)


#for ir
I7 = Pin(27, Pin.IN)
I6 = Pin(26, Pin.IN)
I5 = Pin(22, Pin.IN)
I4 = Pin(21, Pin.IN)
I3 = Pin(20, Pin.IN)
I2 = Pin(19, Pin.IN)
I1 = Pin(18, Pin.IN)
I0 = Pin(17, Pin.IN)

#for pc
clock = machine.Pin(7, machine.Pin.OUT)

# for accumlator
clockState = machine.Pin(6, machine.Pin.OUT,value = 0)
d3 = machine.Pin(0, machine.Pin.OUT,value = 0)
d2 = machine.Pin(1, machine.Pin.OUT,value = 1)
d1 = machine.Pin(2, machine.Pin.OUT,value = 1)
d0 = machine.Pin(3, machine.Pin.OUT,value = 0)
load = machine.Pin(4, machine.Pin.OUT,value = 0)
reset = machine.Pin(5, machine.Pin.OUT,value = 0)

# for updated input from IR
def update_pins():
    # Read values for I0 to I3 separately
    i0 = I0.value()
    i1 = I1.value()
    i2 = I2.value()
    i3 = I3.value()

    # Read values for I4 to I7 separately
    i4 = I4.value()
    i5 = I5.value()
    i6 = I6.value()
    i7 = I7.value()

    print(f"operand: {i3} , {i2}, {i1}, {i0}")
    print(f"opcode: {i7}, {i6}, {i5}, {i4}")

    # Your additional logic here


def accumlator():
    
    clockState.on() if clockState.value() == 0 else clockState.off()
    load.value(1)


def pcIncrement():
    clock.value(1)
    clockState.value(1);
    #utime.sleep_ms(500)
    clock.value(0)
    clockState.value(0);
    # utime.sleep_ms(500)    

        

reset.value(1)
utime.sleep(0.1)
reset.value(0)
#clockState.value(1)
#load.value(0)
pcload.value(0)
accmux.value(0)

while True:

    
    
    #accumlator()
    
    ##load.value(0)
    update_pins()
    load.value(1)
    #A0.value(I0.value())
    #A1.value(I1.value())
    #A2.value(I2.value())
    #A3.value(I3.value())

    #accumlator()
       # Check for operand values and perform corresponding actions
    if I7.value() == 1 and I6.value() == 0 and I5.value() == 1 and I4.value() == 1:  # Operand 1011
        print("Load operation")
      # Perform load operation
        #load = 1
        accmux.value(1)
        ###load.value(1)
        d0.value(I0.value())
        d1.value(I1.value())
        d2.value(I2.value())
        d3.value(I3.value())
        #d1 = I1.value()
        #d2 = I2.value()
        #d3 = I3.value()
        #load=0
        ###clockState.value(1)
        ###clockState.value(0)
        load.value(0)

    elif I7.value() == 0 and I6.value() == 1 and I5.value() == 0 and I4.value() == 1:  # Operand 0101
        print("Add operation")
        # Perform add operation logic here
        #add_sub = 0
        add_sub.value(0)
        A0.value(I0.value())
        A1.value(I1.value())
        A2.value(I2.value())
        A3.value(I3.value())
        accmux.value(0)
        ###load.value(1)
        ###clockState.value(1)
        load.value(0)
        ###clockState.value(0)

    elif I7.value() == 0 and I6.value() == 1 and I5.value() == 1 and I4.value() == 1:  # Operand 0111
        print("Subtract operation")
        #add_sub = 1
        add_sub.value(1)
        A0.value(I0.value())
        A1.value(I1.value())
        A2.value(I2.value())
        A3.value(I3.value())
        accmux.value(0)
        ###load.value(1)
        ###clockState.value(1)
        ###clockState.value(0)
        load.value(0)
        # Perform subtract operation logic here

    elif I7.value() == 0 and I6.value() == 1 and I5.value() == 0 and I4.value() == 0:  # Operand 0111
        print("halt")
        break;

    else:
        print("No valid operand")
    
    pcIncrement()
    utime.sleep(2)

     # Add a 1-second delay between iterations
