from django.urls import path
from .views import *

urlpatterns = [
    path('api/create_user', RegisterUser.as_view(), name='create_user'),
]