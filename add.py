import tvm

tvm.register_datatype("foo", 23)

x = tvm.placeholder((3,), name="x", dtype="custom[foo]32")
y = tvm.placeholder(x.shape, name="y", dtype="custom[foo]32")
z = tvm.compute(x.shape, lambda i: x[i] + y[i])

s = tvm.create_schedule([z.op])
print(tvm.lower(s, [x, y, z], simple_mode=True))
