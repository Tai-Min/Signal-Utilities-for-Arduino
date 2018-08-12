# ExponentialRegulator

Changes value from initial to final in given time in exponential manner.

## Contents
| ExponentialRegulator                                                                                                                                            |
|-----------------------------------------------------------------------------------------------------------------------------------------------------------------|
| + start(T, T, unsigned long): void<br/> + stop(): void<br/> + pause(): void</br> + resume(): void</br> + running(): bool<br/> + paused(): bool<br/> + read(): T |

## Usage
#### ExponentialRegulator variable initializer:
```cpp
template<typename T>
ExponentialRegulator;
```
**T:** Type of the regulator's output variable.<br/>
***
#### Start regulator:
```cpp
void start(T startVal, T stopVal, unsigned long time);
```
+ **startVal:** Start regulation with this value<br/>
+ **stopVal:** End regulation with this value<br/>
+ **time:** Regulation shall take this time (in milliseconds)<br/>
***

#### Stop regulator:
```cpp
void stop();
```
Finishes the task the regulator is currently doing.<br/>
Doesn't do anything if the regulator is not running.<br/>
***

#### Pause regulator:
```cpp
void pause();
```
Does not finish the task the regulator is currently doing, but pauses it.<br/>
Doesn't do anything if the regulator is not running.<br/>
***

#### Resume regulator:
```cpp
void resume();
```
Doesn't do anything if the regulator is not running.<br/>
<br/>

#### Check whether regulator is running:
```cpp
bool running();
```
+ **returns:** true if regulator has not finished it's task, even if it's paused.<br/>
***

#### Check whether regulator is paused:
```cpp
bool paused();
```
+ **returns:** True if the regulator is paused.<br/>
***

#### Get current value from ExponentialRegulator:
```cpp
T read();
```
+ **returns:** New value for running regulator. If the regulator is not running, returns the last value it computed when it was running or 0 if the regulator was never started.