from concurrent import futures
import time

import grpc

import test_pb2
import test_pb2_grpc

_ONE_DAY_IN_SECONDS = 60 * 60 * 24


# test_pb2_grpcのMyGrpcServicer()を実装
class MyGrpc(test_pb2_grpc.MyGrpcServicer):

    def GetSomething(self, request, context):

        # いろんな処理はここで

        print("Someone requested something!")
        # データ取得は`request.xxx`でできて分かりやすい
        print(f'int_param: {request.int_param}')
        print(f'str_param: {request.str_param}')

        # 必ず設定したresponseを返却する
        response = test_pb2.MyResp(status=200, message="Great message.")
        return response


def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    # MyGrpc()を使うよ！と登録しているかんじ
    test_pb2_grpc.add_MyGrpcServicer_to_server(MyGrpc(), server)
    # portの設定
    server.add_insecure_port('[::]:50051')
    server.start()
    try:
        while True:
            time.sleep(_ONE_DAY_IN_SECONDS)
    except KeyboardInterrupt:
        server.stop(0)


if __name__ == '__main__':
    print("start")
    serve()