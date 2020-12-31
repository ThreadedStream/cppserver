<h1>HTTP Server using Boost.Asio 1.72</h1>

<img src="assets/image0.png" width=750px height=400px>

<p>Being inspired by Boost.Asio HTTP Server implementation and Django web framework, i have come up with an idea of developing my own one</p>
<p>In the very beginning, couple goals were set. Here are some of them:</p>
<ol>
  <li><b>Dynamic loading of template and static files</b></li>
  <li><b>Set up a connection to a database server, so to enable a user to carry out sign up operation</b></li>
</ol>

<h1>How does it work?</h1>
<p>To be honest, i have cheated a bit. For the sake of clarity, i want to point out that not all operations are directly executed by asio server.</p>
<p>Instead, it serves as a kind of intermediate layer between a user and django server,which runs in separate terminal.</p>
<p>For example, consider a classical scenario of writing data to a database</p>
<p>As was mentioned previously, asio server is nothing but an intermediate layer between django server and user. So it makes sense to run django server first
   to request database reads and writes</p>

<img src="assets/django.png" width=750px height=400px>

<p>Note that you should run it on port 5600 to make it work</p>
<p>Next, you should open up your browser and navigate to the following page</p>

<img src="assets/signup.png" width=500px height=600px>
<p>You may create your own user by filling out all fields</p>
<p>To ensure that database operation was successfully completed, you may navigate to http://127.0.0.1/users</p>
<p>Aforementioned page contains all of the json data retrieved from a django server</p>
<img src="assets/json.png" width=300px height=300px>

