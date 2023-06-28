# ViragoBox

ViragoBox is a DMX-controlled video renderer for Sonia Sabri's contemporary dance piece [*Virago*](https://www.ssco.org.uk/productions/touring/virago/virago.php). It can run either as a desktop application, or directly from the command-line without a window manager (Linux only).

## Building ViragoBox (Linux, macOS)

### Requirements

- CMake
- C++ compiler supporting C++14
- SFML 2
- Boost C++ Libraries (log, program_options)
- Open Lighting Architecture

### Optional Requirements

- Doxygen (to build documentation)

### Building

```
$ cd build
$ cmake ..
$ make
$ make install
```

### Building Documentation

```
$ make doc
```

HTML documentation is located at ```build/doc/html/index.html```

## Usage

The installed binary is located at ```bin/viragobox```

```
Usage viragobox [options]
Options:
  -h [ --help ]             Print this message and exit
  -d [ --debug ]            Show debug messages
  -a [ --address ] arg (=1) Start address
  -r [ --resolution ] arg   Resolution of the render window
  -f [ --fullscreen ]       Render to the entire display
  ```
  
## DMX Fixture Personality

<table>
  <thead>
    <tr>
      <th>Slot</th>
      <th>Function</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>1</td>
      <td>Intensity</td>
    </tr>
    <tr>
      <td>2</td>
      <td rowspan="2">Position X</td>
    </tr>
    <tr>
      <td>3</td>
    </tr>
    <tr>
      <td>4</td>
      <td rowspan="2">Position Y</td>
    </tr>
    <tr>
      <td>5</td>
    </tr>
    <tr>
      <td>6</td>
      <td rowspan="2">Width</td>
    </tr>
    <tr>
      <td>7</td>
    </tr>
    <tr>
      <td>8</td>
      <td rowspan="2">Height</td>
    </tr>
    <tr>
      <td>9</td>
    </tr>
    <tr>
      <td>10</td>
      <td>Red</td>
    </tr>
    <tr>
      <td>11</td>
      <td>Green</td>
    </tr>
    <tr>
      <td>12</td>
      <td>Blue</td>
    </tr>
    <tr>
      <td>13</td>
      <td>Line Weight</td>
    </tr>
    <tr>
      <td>14</td>
      <td>Control Channel</td>
    </tr>
  </tbody>
</table>

X/Y positions are centered at 50%.


<h3>Control Channel Values</h3>

#### 0-253  Normal operation

#### 254    Colour bars
<img alt="Screenshot of the colour bars test pattern" src="https://github.com/dougfinl/ViragoBox/blob/master/doc/images/viragobox_colorbars.png" width="480">

#### 255    Line-up grid
<img alt="Screenshot of the line-up grid" src="https://github.com/dougfinl/ViragoBox/blob/master/doc/images/viragobox_lineup.png" width="480">

