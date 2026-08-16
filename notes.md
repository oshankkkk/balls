
# Elastic collisons
#### (Relearning physics cause i dont remember shit from school)
Elastic collision is when 2 objects collide and they are not intact after the collision and no energy is lost in the process. If some enegry is lost its a apporximate elastic collision. If the 2 objects collide and move in 1 blob mass, its a perfect elastic incollison.

##### References
Elastic collisions: https://youtu.be/M2xnGcaaAi4?si=1Fg-H-VqkGXTckAM
Vectors: https://youtu.be/Ej3ZVxljJfo?si=vD_4lobvDFK3ZdFm
Collisions systems: https://youtu.be/dJNFPv9Mj-Y?si=-EGnxlr642aCHrX-

#### Making Stable collisions
###### Finding the vector between the centers

Suppose the centers are,
[
P_1=(x_1,y_1)
]
[
P_2=(x_2,y_2)
]
[
\Delta x=x_2-x_1
]
[
\Delta y=y_2-y_1
]

So the vector from ball 1 to ball 2 is:

[
\vec d=(\Delta x,\Delta y)
]

For example, if:
[
P_1=(2,3),\qquad P_2=(5,7)
]

[
\vec d=(3,4)
]

###### Finding the distance

Pythagoras:
[
d=\sqrt{\Delta x^2+\Delta y^2}
]
[
d=\sqrt{3^2+4^2}=5
]

###### Dividing the vector by its length for the unit vector

[
n_x=\frac{\Delta x}{d}
]
[
n_y=\frac{\Delta y}{d}
]

[
n_x=\frac35=0.6
]
[
n_y=\frac45=0.8
]

[
\vec n=(0.6,0.8)
]

We do this to find the direction of the collision, not the whole vector. The whole vector thats the steps but not the direction explictly (or somthing i that).

The vectors between the balls have different lengths, but their direction is the same. When we divide by the distance, we remove the length information and keep only the direction.

> The vector vid explains

#### Reflecting particles

**Only the part of their velocity pointing into each other needs to be reversed.**

We take the realtive velocities of the particles

```cpp
double rvx = v1.x - v2.x;
double rvy = v1.y - v2.y;
```

Then find how much of that is in the collision direction.

Use the dot product:

```cpp
double velAlongNormal = rvx * nx + rvy * ny;
```

[
v_{relative}\cdot n
]


If they're moving toward each other, bounce them

```cpp
double impulse = -velAlongNormal;
```

Apply it in opposite directions:

```cpp
agents[x].velocity.x += impulse * nx;
agents[x].velocity.y += impulse * ny;

agents[i].velocity.x -= impulse * nx;
agents[i].velocity.y -= impulse * ny;
```

###### The actual physics concept

You can think of the velocity as:

```text
velocity
   ↙
  /|
 / |
/  |
↑  ↑
normal   tangent
```

The collision only needs to change the **normal part**.

The tangential part stays the same for frictionless balls.

So:

```text
BEFORE

velocity = normal component + tangent component


COLLISION

normal component → reversed
tangent component → unchanged


AFTER

velocity = -normal component + tangent component
```

The formula for reflecting one velocity off a surface is:

[
\boxed{v' = v - 2(v\cdot n)n}
]

> But for two moving balls, you generally don't just reflect each ball's velocity independently. You use their relative velocity and masses, which leads to the collision impulse equation.

Next step with two balls of equal mass, draw the vectors, and derive the impulse equations.

