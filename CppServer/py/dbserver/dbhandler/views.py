from django.shortcuts import render
from django.http import HttpResponse
from rest_framework.views import *
from .serializers import * 
import datetime
from rest_framework.response import Response
from rest_framework import status
from rest_framework.permissions import AllowAny




def home_page(request):
    now = datetime.datetime.now()
    return render(request, template_name='index.html', 
                context={'now': now})


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

    