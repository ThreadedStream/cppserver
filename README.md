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
<p>Instead, it serves as a kind of intermediate layer between a user and django server,which is runs in separate terminal.</p>
<p>For example, consider a classical scenario of writing data to a database</p>
