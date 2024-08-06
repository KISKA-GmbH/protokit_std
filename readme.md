# Protokit

The protokit is designed to allow fast prototyping. It supports basic functionalities for input and output.

# Event Passing

The implementation of functionality is based on event passing. There are three event components: Sender, Store, and
Reader(Receiver).

## Sender

The sender emits events to the store or directly to a receiver.

## Store

The store stores the events and makes them read accessable by readers.

## A Reader or Receiver

A reader or receiver reads the events from the store or receives them directly from the sender. And executes action
based on the event.