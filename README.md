# TVM Custom Datatype Samples

Clone this repository with `git clone --recursive`. This will also clone my fork of TVM, which is included as a submodule.

Build the TVM submodule in the `tvm` folder.
Instructions for building TVM can be found [here](https://docs.tvm.ai/install/from_source.html#build-the-shared-library).
TVM will need to be built with the optional LLVM dependency.
The easiest way to do this on Linux is to install LLVM from the [nightly Ubuntu build](https://apt.llvm.org/) as described in the TVM documentation.
Then, when running CMake to generate the TVM build files, add `-DUSE_LLVM=ON` to your command-line options.

Once TVM is built, we must ensure that Python picks up this version of TVM as we run the samples.
This can be done by modifying the `PYTHONPATH` environment variable.
On Linux, for example:
```bash
export TVM=/path/to/tvm/submodule
export PYTHONPATH=${TVM}/python:${TVM}/topi/python:${TVM}/nnvm/python:${PYTHONPATH}
```

Run CMake to create the scripts which will run the tests. On Linux:
```bash
mkdir build && cd build
cmake ..
```

Finally, we can run the tests, which are our samples. The tests are listed in the `CMakeLists.txt`.
To run all of them and see the output on Linux:
```bash
ctest --verbose
```
