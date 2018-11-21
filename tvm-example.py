import numpy as np

import nnvm.compiler
import nnvm.testing
import tvm
from tvm.contrib import graph_runtime

x = tvm.placeholder((3,), name="x", dtype="mycustomtype")
y = tvm.placeholder(x.shape, name="y", dtype="mycustomtypetwo")
z = tvm.compute(x.shape, lambda i: x[i] + y[i])

print(z.debug_str())

# batch_size = 1
# num_class = 1000
# image_shape = (3, 224, 224)
# data_shape = (batch_size,) + image_shape
# out_shape = (batch_size, num_class)
# 
# net, params = nnvm.testing.resnet.get_workload(
#     layers=18, batch_size=batch_size, image_shape=image_shape)
# print(net.debug_str())
