import struct

name = "testik_gcs-20220703T195601.bin"
oname = "testik_gcs-20220703T195601.bin.new_raw"

with open(name, mode="rb") as istream, open(oname, mode="wb") as ostream:
	while True:
		time_raw = istream.read(8)
		if not time_raw:
			break

		t = struct.unpack("d", time_raw)
		size_bytes = istream.read(1)
		size = size_bytes[0]
		packet = istream.read(size)

		print(size, t, packet)
		ostream.write(packet)
		ostream.flush()

