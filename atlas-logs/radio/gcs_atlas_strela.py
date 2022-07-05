import sys
import argparse
import time
import struct
import datetime
import zmq

from RF24 import RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
from RF24 import RF24_1MBPS, RF24_250KBPS, RF24_2MBPS
from RF24 import RF24_CRC_16, RF24_CRC_8, RF24_CRC_DISABLED
from RF24 import RF24 as RF24_CLASS
from RF24 import RF24_CRC_DISABLED
from RF24 import RF24_CRC_8
from RF24 import RF24_CRC_16


radio2=RF24_CLASS(24, 1)
#radio2=RF24_CLASS(22, 0)


def generate_logfile_name():
    now = datetime.datetime.utcnow().replace(microsecond=0)
    isostring = now.isoformat()  # string 2021-04-27T23:17:31
    isostring = isostring.replace("-", "")  # string 20210427T23:17:31
    isostring = isostring.replace(":", "")  # string 20210427T231731, oi ?oi iaai
    return "testik_gcs-" + isostring + ".bin"

gyro_calib = [0.5174269005847948, -3.421812865497076, -0.24684210526315856]

if __name__ == '__main__':
    static_payload_size = 32

    radio2.begin()

    radio2.openReadingPipe(1, b'\x9a\x78\x56\x34\x12')

    radio2.setCRCLength(RF24_CRC_8)
    radio2.setAddressWidth(5)
    radio2.channel = 100
    radio2.setDataRate(RF24_250KBPS)
    radio2.setAutoAck(True)


    if static_payload_size is not None:
        radio2.disableDynamicPayloads()
        radio2.payloadSize = static_payload_size
    else:
        radio2.enableDynamicPayloads()

    radio2.enableOnlyAckPayload()

    radio2.startListening()
    radio2.printDetails()

    zmq_ctx = zmq.Context()
    pub_socket = zmq_ctx.socket(zmq.PUB)
    pub_socket.bind("tcp://0.0.0.0:1234")

    filename = generate_logfile_name()
    f = open(filename, 'wb')
    fname_raw = filename + ".raw"
    fraw = open(fname_raw, 'wb')
    #summ = [0, 0, 0]
    #count =f 0
    while True:
        has_payload, pipe_number = radio2.available_pipe()
        #print(f'has_payload-{has_payload}, pipe_number={pipe_number}')

        if has_payload:
            payload_size = static_payload_size
            if payload_size is None:
                payload_size = radio2.getDynamicPayloadSize()

            data = radio2.read(payload_size)
            #print('got data %s' % data)
            packet = data
            packet_size = len(packet)
            biter = struct.pack("<B", packet_size)
            unix = time.time()
            p_unix = struct.pack("<d", unix)
            record = p_unix + biter + packet
            f.write(record)
            f.flush()

            try:
                if data[0] == 255:
                    pass
                    print("==== Пакет МА тип 1 ====")
                    unpack_data = struct.unpack("<BHI2fh2fhHBH", data)
                    print ("время:", unpack_data[2])
                    print ("номер:", unpack_data[1])

                    print ("температура БМП:", unpack_data[4])
                    print ("давление БМП:", unpack_data[3])

                    print ("темп дс18б20:", unpack_data[5]/10)

                    print ("широта:", unpack_data[6])
                    print ("долгота:", unpack_data[7])
                    print ("высота:", unpack_data[8])
                    print ("куки:", unpack_data[9])
                    print ("фикс:", unpack_data[10])
                    #summ[0] += ([x/1000 for x in unpack_data[9:12]])[0]
                    #summ[1] += ([x/1000 for x in unpack_data[9:12]])[1]
                    #summ[2] += ([x/1000 for x in unpack_data[9:12]])[2]
                    #count += 1
                    #print([x/count for x in summ])
                elif data[0] == 254:
                    pass
                    print("==== Пакет МА тип 2 ====")
                    unpack_data = struct.unpack("<BHI9hfBh", data)
                    print ("время:", unpack_data[2])
                    print ("номер:", unpack_data[1])

                    print ("гиро ЛСМ:", [(unpack_data[6:9][i]/1000 - gyro_calib[i]) for i in range(3)])
                    print ("аксел ЛСМ:", [x/1000 for x in unpack_data[3:6]])
                    print ("магн:", [x/1000 for x in unpack_data[9:12]])
                    print ("люксы:", unpack_data[12])
                elif data[0] == 250:
                    unpack_data = struct.unpack("<BBHIIhH6hH", data[:30])
                    print("==== Пакет ДА", unpack_data[1], " тип 1 ====")

                    print ("время:", unpack_data[3])
                    print ("номер:", unpack_data[2])

                    print ("температура БМП:", unpack_data[5]/100)
                    print ("давление БМП:", unpack_data[4])
                    print ("влажность БМП:", unpack_data[6])
                    print ("аксел ЛСМ:", [x/1000 for x in unpack_data[7:10]])
                    print ("гиро ЛСМ:", [x/1000 for x in unpack_data[10:13]])

                elif data[0] == 251:
                    unpack_data = struct.unpack("<BBHI3fBBH", data[:24])
                    print("==== Пакет ДА", unpack_data[1], " тип 2 ====")
                    print ("время:", unpack_data[3])
                    print ("номер:", unpack_data[2])

                    print ("лат:", unpack_data[4])
                    print ("лон:", unpack_data[5])
                    print ("хейгхт:", unpack_data[6])
                    print ("фикс:", unpack_data[7])
                else:
                    print('got data %s' % data)
            except Exception as e:
                print(e)
            print(data)
            #print(data[0])
            #print('got data %s' % data)
            fraw.write(data)
            fraw.flush()
            try:
                pub_socket.send_multipart([packet], zmq.DONTWAIT)
            except Exception as e:
                print("unable to send data to socket")
        else:
            print('got no data')
            pass
        time.sleep(0.1)
