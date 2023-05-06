# Crumple

Alex, Aydin, and Han implementing a wave function collapse algorithm for Software Systems SP23.

This project uses wavefunction to collapse to implement grid-based procedural image generation.

## Installation
Due to all devs of this project running linux operating systems, all compatilibity has only been verified on linux systems.
### Installing STB / STB_image
1. Clone the project's git repository:
```C
$ git clone https://github.com/nothings/stb.git
```
2. Copy the relevent header files into your include folder (example below given for Ubuntu, and will require root permissions):
```C
$ sudo cp stb/stb_image.h /usr/local/include/
```

### Installing Crumple

1. Clone this repository:
```C 
$ git clone https://github.com/olincollege/crumple.git
```
2. Build this project: 
```C 
$ mkdir build && cd build
$ cmake ..
$ make
```


## Usage instructions
To input images and rules, you'll need to create a yaml config file and an directory to store your images (and put your images there). See example.yaml and example_imdir for examples. Please note that the yaml parsing is tempermental, so please stick to the formatting in the example as closely as possible.

To generate your procedurally-generated image, run the main executable generated using the argument as the path to your configuration yaml. To run the example, run: ```./build/src/main example.yaml```

### Usage Notes
1. It is difficult to create an internally consistent tiling rule that will not create an error so be prepared for your first few attempts to give a ```modulous 0 attempted``` error.
2. There are a few unique edge-cases that our brittle parser can occasionally struggle with. One of these being tile names... If the parser, decidely does not appreciate your chosen tile name, change it. Seriously, this is the only fix that we have found to this issue.

## Dependencies
STB_image

GCC 12.1.0 (other compilers may work but are not guaranteed to.)

## Known Bugs
When inputting image filenames, an extra character is sometimes added to the end during parsing for unknown reasons, which causes issues. Putting the tiles configurations with the shorter (length) names first in the yaml may fix this, as may changing the filenames.

Running the parser tests causes malloc errors on some machines and run smoothly on others. The cause of this is unknown. These tests all run successfully on at least one (Han) team member's machine.  An example error message: `malloc(): invalid size (unsorted)`