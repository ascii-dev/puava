import sys
import pytest
from greet.greet import greet


def test_greet():
    assert greet() == "Hello from Puava Python Greet!"
