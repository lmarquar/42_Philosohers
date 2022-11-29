# 42_Philosohers
it is a famous coding game, brought into the world by Edsger W. Dijkstra and it's about resource managment.

Here a brief explanation:
there is a number x of philosophers sitting around a round table, and
in between each of them there is a fork, infront of each is a plate with food
always ready served. To eat a philosopher needs two forks and he's only allowed
to grab those next to him. If there is a philosopher already using the fork he wants,
he has to wait until the other one finished. There is two other states that a philosopher
can have, it's sleeping and philosophizing.

Now let's get to the input arguments. there is 3-4.
  number_of philosophers: is selfexplanatory.
  time_to_die: is the time in milliseconds a philospher has to get from one meal to the next one.
It resets when the philospher started eating and if it ran out before he started eating, he dies
and the program terminates after displaying a death message.
  time_to_eat: is the time in milliseconds it takes a philosopher to eat.
  time_to_sleep: is like time to eat, but for sleeping. a philosopher always sleeps inbetween his meals
for this duration. Afterwards he either philosophizes if there is not enough forks, or goes instantly over
to eating again.
  [number_of_times_each_philosopher_must_eat]: is optional. It makes the program terminate after every
philosopher ate atleast this many times.
 
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

Hope this explained it well enough, if not just google "the dining problem".
