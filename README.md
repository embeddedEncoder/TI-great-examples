# TI-great-examples\
Create a self-contained CCS project for all to use. The example projects shall have all the common and include headers along with driverlib functionality right within the project so no one has to go back to the C2000Ware. This is to increase a programmers productivity by reducing time taken to setup a CCS project.

## What this project is:
1. A comprehensive set of example files that have all device level dependencies and libraries already set up in the CCS project
  - So, when you download a project and open it up, it works without any issues. No linking to local directories, symbols etc...
2. Something that enables git versioning for a CCS project
  - Anyone who has worked with CCSs' C2000Ware examples knows how unintutive it is to setup a git repo for any project that one is working on
  
## What this project is not:
1. Something that gets rid of CCS. We still want everyone to use CCS Studio
  - if you are looking for ways to get rid of CCS altogether see: 
    - [Yet Another Command Line (Program)](https://github.com/NicolasRodriguez676/yacl)
    - [C2000 CMake toolchain] (https://gist.github.com/farrrb/032dcb907a0787ede67173fe68f97915). Also see this [thread](https://www.reddit.com/r/embedded/comments/s6r1vn/what_is_cmake_and_how_do_i_use_it_to_ease/)
2. Something that spans other microcontroller architectures, like PIC, AVR, etc... 
  - Infact, if anone wants to do this, they should start setting up another GitHub project and start setting up goals like this project, so it is much more streamlined to the community. We shoud strive to keep these examples more or less to TI's MCU portfolio.

## License

[MIT License](LICENSE)
