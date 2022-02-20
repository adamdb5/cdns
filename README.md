# cdns

![Build and Test badge](https://github.com/adamdb5/cdns/actions/workflows/build_and_test.yaml/badge.svg)

A simple, DNS message marshalling / unmarshalling library written in C.

cdns facilitates the marshalling and unmarshalling of DNS messages. 

cdns does not contain any way of sending / receiving messages, however cdns can marshall the message so it is ready to send directly over a socket or via another protocol such a DoT / DoH.

