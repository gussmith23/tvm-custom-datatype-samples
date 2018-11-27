import tvm
import topi

tvm.register_datatype("foo", 23)
tvm.register_datatype("bar", 24)

x = tvm.placeholder((3,), name="x", dtype="custom[foo]32")
y = topi.cast(x, dtype="custom[bar]32")

s = tvm.create_schedule([y.op])
print(tvm.lower(s, [x, y], simple_mode=True))
