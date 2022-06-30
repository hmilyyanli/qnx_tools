#!/bin/bash

g++ -g -c nvsci_config_json_file_provider.cpp -I/home/chf1cgd4/00.prj/pjw3/.conan/data/tiny_json/0.1.0+5d4a1cb48c/aos/dev/package/0912397307c6724dc4bf828422c8af796ac1f047/include/tiny_json -I./include
g++ -g -c main.cpp -I/home/chf1cgd4/00.prj/pjw3/.conan/data/tiny_json/0.1.0+5d4a1cb48c/aos/dev/package/0912397307c6724dc4bf828422c8af796ac1f047/include/tiny_json -I./include
g++ -g -o a.out main.o nvsci_config_json_file_provider.o -L/home/chf1cgd4/00.prj/pjw3/.conan/data/tiny_json/0.1.0+5d4a1cb48c/aos/dev/package/0912397307c6724dc4bf828422c8af796ac1f047/lib -ltiny_json
