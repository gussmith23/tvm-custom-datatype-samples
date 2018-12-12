import tvm
import topi
import numpy as np
import tvm.ir_pass as ir_pass
import ctypes

tgt = "llvm"

tvm.register_datatype("myfloat", 24)

X = tvm.placeholder((3,), name="X")
Y = topi.cast(X, dtype="custom[myfloat]32")

# Create schedule and lower, manually lowering datatypes. Once datatype lowering
# is integrated directly into TVM's lower/build process, we won't need to do
# this manually.
s = tvm.create_schedule([Y.op])
flist = tvm.lower(s, [X,Y])
flist = [flist]
flist = [ir_pass.LowerDatatypes(func, tgt) for func in flist]

cast = tvm.build(flist[0], target=tgt)

ctx = tvm.context(tgt, 0)
x = tvm.nd.array(np.random.uniform(size=3).astype(X.dtype), ctx)
y = tvm.nd.empty(Y.shape, dtype=Y.dtype, ctx=ctx)

cast(x,y)

# We're not able to print y, as under the hood TVM tries to convert it to a
# numpy array (and numpy won't recognize custom datatypes). So instead we
# copy the raw bytes to a uint32 array.
np_arr = np.empty(y.shape, dtype="uint32")
y.copybytesto(np_arr)

print(" x: " + str(x))
print(" y: " + str(np_arr))
