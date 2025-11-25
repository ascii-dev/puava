"""A custom macro that runs pytest on the given source files."""
load("@rules_python//python:defs.bzl", "py_test")
load("@pypi//:requirements.bzl", "requirement")

def puava_pytest(name, srcs, deps = [], args = [], **kwargs):
    # Identify the primary test file (usually the first source)
    test_file = srcs[0]

    py_test(
        name = name,
        main = "//python/tests:pytest_main.py",
        srcs = srcs + ["//python/tests:pytest_main.py"],
        deps = deps + [
            requirement("pytest"),
        ],
        # $(location :test_file) tells Bazel to resolve the path.
        args = args + ["$(location :%s)" % test_file], 
        **kwargs
    )
