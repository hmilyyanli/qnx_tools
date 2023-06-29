# README

## Introduction

This is the repository for the Daily C++ talks. The idea of Daily C++ has been
taken from a [blog][1] of Jonathan Boccara. The Daily C++ talks are in some
sense an internal self-organized training to share C++ knowledge and techniques
for interested colleges. This repository collects previous slides of the talk
and code snippets.

A wiki for the next upcoming talks can be found [here][2]. Suggestions for next
topics can also be found there.

Uploaded Videos can be found on the [wiki][2].

## Ideals for Daily C++

A Daily C++ talk:

  1. should be short enough to fit in any schedule (developers do not have much
     time)
  2. should once a day place
  3. should be available for everybody
  4. should by people of the company for people of the company (internal
     training),

To satisfy point 1. and 4. we expect that a talk

  * lasts at most 10 minutes,
  * is filmed and uploaded on some share.

## Video List

- Daily C++ - Ep 2 - TMP 2 (enable_if): https://tube.video.bosch.com/media/Daily+C%2B%2B+-+Ep+2+-+How+to+use+%27enable_if%27/0_2acr8hcr
- Daily C++ - Ep 3 - Concepts: https://tube.video.bosch.com/media/Daily+C%2B%2B+-+Ep+3+-+C%2B%2B20+concepts/0_etnwlr17
- Daily C++ - Ep 6 - Move and Embedded (Part 2): https://tube.video.bosch.com/media/Daily+C%2B%2B+-+Ep+6+-+Move+and+Embedded+Part+2/0_hwhegsli
- Daily C++ - Ep 7 - Object Oriented Programming: https://tube.video.bosch.com/media/Daily+C%2B%2B+-+Ep+7+-+Object+Oriented+Programming/0_hxz7eww2
- Daily C++ - Ep 8 - State Pattern: https://tube.video.bosch.com/media/Daily+C%2B%2B+-+Ep+8+-State+Pattern/0_v9iki08x/
- Daily C++ - Ep 9 - Pattern Code Example: https://tube.video.bosch.com/media/Daily+C%2B%2B+-+Ep+9+-+State+Pattern+Code+Example/0_5uzaptvc
- Daily C++ - Ep 10 - Chain of Responsibility: https://tube.video.bosch.com/media/Daily+C%2B%2B+-+Ep+10+-+Chain+of+Responsibility+Pattern/0_rkwbzbmo
- Daily C++ - Ep 11 - Chain of Responsibility: https://tube.video.bosch.com/media/Daily+C%2B%2B+-+Ep+11+-+Chain+of+Responsibility+Code+Example/0_6vy2ust2
- Daily C++ - Ep 12 - Iterator Pattern: https://tube.video.bosch.com/media/Daily+C%2B%2B+-+Ep+12+-+Iterator+Pattern/0_9i2vjf34
- Daily C++ - Ep 13 - Iterator Pattern Code Example: https://tube.video.bosch.com/media/Dailay+C%2B%2B+-+Ep+13+-+Iterator+Pattern+Code+Example/0_1o4tbjmo
- Daily C++ - Ep 14 - Static Initialization Order: https://tube.video.bosch.com/media/Daily+C%2B%2B+-+Ep+14+-+Static+Initialization+Order+Fiasco/0_jh56jffn
- Daily C++ - Ep 15 - Static Initialization Order Example: https://tube.video.bosch.com/media/Daily+C%2B%2B+-+Ep+15+-+Static+Initialization+Order+Fisasco+Example/0_gcwnqkxq
    
[1]: https://www.fluentcpp.com/dailycpp/ "Daily C++"
[2]: https://inside-docupedia.bosch.com/confluence/pages/viewpage.action?pageId=1060352608 "Docupedia"
[3]: https://www.fluentcpp.com/dailycpp/ "Bosch YouTube"

## Content
2019_09_27_talk_1: Template Meta Programming (TMP)
2019_09_30_talk_2: Template Meta Programming (TMP)
2019_10_01_talk_3: Template Meta Programming (TMP)
2019_10_14_talk_4: A polymorphic class should suppress copying (Cpp Core Guidelines)
2019_10_21_talk_6: std::move(): 1. move rvalue will call class's move constractor. 2. use & and && in function defination of class to specify the lvalue and rvalue.
2019_10_22_talk_7: recommanded c++ books
2019_10_28_talk_8 & 2019_11_06_talk_9: internal state change design pattern
2019_12_05_talk_14: static initialization order fiasco (SIOF) and howto break it.
2020_05_08_talk_18: slice object copy, and use virtual assignment function seems can avoid this, see: https://stackoverflow.com/questions/274626/what-is-object-slicing for details
/2020_05_19_talk_24: never mixed signed and unsigned type
2020_05_27_talk_27: prefer uniform init format
2020_07_02_talk_41: raii
2023_04_19_talk_strong_types: it's recommanded to use strong types for detect errors earlier at compile time
2023_06_08_SimOnlyVar: variable only used during simulation/debug, will skip the defination when release. the cost is empty class size(1 byte) occupied.
