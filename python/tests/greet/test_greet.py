from greet.greet import greet


def test_greet() -> None:
    assert greet() == "Hello from Puava Python Greet!"
