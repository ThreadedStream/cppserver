from django.shortcuts import render
from rest_framework.views import *
from .serializers import * 
from rest_framework.response import Response
from rest_framework import status
from rest_framework.permissions import AllowAny

class RegisterUser(APIView):
    serializer_class = UserSerializer
    permission_classes = (AllowAny,)

    def post(self, request, format=None):
        data = {}
        ser_json = {}
        ser_json['first_name'] = request.data['first_name']
        ser_json['last_name']  = request.data['last_name']
        ser_json['email']      = request.data['email']
        ser_json['password']   = request.data['password']

        user = UserSerializer(data=ser_json)
        if user.is_valid():
            user.save()
            data['success'] = True
            data['result']  = True
            return Response(data=data, status=status.HTTP_200_OK)
        else:
            data['success'] = False
            data['result']  = user.errors
            return Response(data=data, status=status.HTTP_400_BAD_REQUEST)

    

        