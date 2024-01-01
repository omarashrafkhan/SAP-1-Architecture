# Digital Logic Design Project -SAP 1

**Author:** Bupendar Jogi  
**Date:** November 17, 2023

## Project Description

In this Digital Logic Design (DLD) project, our team aims to design a Simple As Possible-1 (SAP-1) computer. The SAP-1 architecture serves as an excellent starting point for understanding the fundamentals of computer organization and digital logic.

The SAP-1 computer is designed to be simple yet educational, making it an ideal project for learning the basics of digital logic circuits, microarchitecture, and assembly language programming. Our project will involve the design and implementation of various components, including the instruction register, arithmetic and logic unit (ALU), control unit, and memory.

We plan to explore the step-by-step process of building the SAP-1 computer, starting from the basic building blocks and gradually progressing to a fully functional system. This project will not only enhance our understanding of digital logic principles but also provide hands-on experience in constructing a simple computer system.

## Group Members
- Omar Ashraf - 26985
- Rohan Riaz
- Jawad
- Hamza Moosani
- Zain Sharjeel
- Ramail
- Zeeshan Zai
- Safwan

## Project Usage and Instructions

The complete project, including the source code, documentation, and additional details, is available on our [GitHub repository](link-to-repository). However, if you want, you can visit the [Wokwi link](https://wokwi.com/projects/385295816149947393) below to simulate the project on the online platform.

**Guidelines:**
A brief flow of information is as such that the clock of the SAP-1 is controlled by the Raspberry Pi itself. This clock ticks to ensure that the Program counter always points to the next instruction being executed. There are a total of 4 memory locations, each of which contains an 8-bit instructional data type. This is divided into the first 4 bits for the instruction and the last 4 bits for the data. Each time an instruction is being executed, the values from the memory address get fetched and put into the instruction and data register. After this, the I and D register instruct the Control Unit (Raspberry Pi) on what to do based on the opcode given below: 1011 for LOAD, 0101 for ADD, 0111 for SUB, 0100 for HALT. At each instant, the values that the instruction executes are stored in the accumulator shown using the 7-segment display in hexadecimal.

**Usage:**
You can change the values in each of the memory chips to execute a different instruction with different data by going into 'c' files. Memory chips are: memory, memory2, memory3, memory4.

For any inquiries, feedback, or collaboration opportunities, please feel free to reach out through the [GitHub repository's communication channels](link-to-communication-channels).
