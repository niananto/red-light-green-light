# traffic-light-controller

Video demostration can be found [here](https://youtu.be/9mWLkRmKQEA)

### A traffic light controller for 4 ways crossing and barricade controller for trains  
  
This project can be recreated by using 2 Arduinos. We used Arduino UNO R3 but you can use Mega too. One of them should be uploaded the file road/roadV2/roadV3/simpleRoadFinal and the other should have the file named train.  

## Road

The algorithm works as a scheduling algorithm with dynamic ratio/weight with no starvation. As we know the number of roads (3/4/5 usually) in a crossing, it is easy to hardcode that into the program.  

1. Take inputs from the IRs and count the current number of cars every 1ms. IRs at the beginning of the road increments the count and the IRs at the end of the road decrements it.
2. There should be a `CYCLE_TIME` by which all the roads should be done with one cycle. We took a cycle time of 20 seconds for a smooth and fast demonstration.
3. Now according to the number of cars in a road, it should be allocated a time and the that time would be subtracted from `timeRemaining`, which is being initialized to `CYCLE_TIME` after every cycle.
4. We had a `timeCounter` which increases every 1ms and now we shall assign a `timeTillStuck` according to the allocated time to that particular road.
5. We have to turn that road GREEN and the others RED for sure. So we turn that raod YELLOW first, turn other roads RED (via YELLOW obviously) and then after a delay of 2ms we turn this road GREEN.
6. This particular road should not become RED after it completes its allocated time aka `timeTillStuck`. After that we would do the same with the remaining roads in that cycle and allocate time to each according to their current circumstances. 

Fun Fact : After we are done with one road in a cycle, we would not bother to have that again before that particular cycle ends. This may be the only fault of this algorithm.

## Train

We used another pair of IRs to detect the train. If one IR detects a train, we simply roates our SERVO Motor and se the barricades down. After another IR detects the train, that means the train has already left the road, we turn the barricades up again.

Not having individual track controls and the ability to handle concurrent trains could be a downside to this approach.
