# Game Controllers
The only predefined controller I have is *Ion Audio Drum Rocker for Playstation(R)3*.

## Ion Audio Drum Rocker for Playstation(R)3

| drum or cymbal | 1-indexed combo* |
| -------------- | ----- |
| <span style="color:red">snare</span>        | 3,11       |
| <span style="color:yellow">tom-tom 1</span> | 4,11       |
| <span style="color:yellow">hihat</span>     | 4,12, up   |
| <span style="color:blue">tom-tom 2</span>   | 1,11       |
| <span style="color:blue">ride</span>        | 1,12, down |
| <span style="color:green">tom-tom 3</span>  | 2,11       |
| <span style="color:green">crash</span>      | 2,12       |

I don't know why sometimes the controller window shows only the first number of a combo instead of all.

\* See [Add a controller](##Add-a-controller) section for details.

## Inspect controller buttons
Here is how to open controller properties window to inspect what buttons are pressed.
![](set-up-usb-game-controllers.png)
![](controller-properties.png)

Hit buttons and see what lights up.

## Add a controller
After you have inspected your controller, to set it up just open `config.json` and put appropriate values there.

**One key thing to remember** is that joystick buttons in the config are zero-indexed. If a button 1 lights up, write 0, for button 2 write 1 etc.