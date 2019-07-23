<html>  
<head>  
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.3.0/jquery.min.js"></script>  
<script>  
setInterval(  
function()  
{  
$('#content').load('read-data.php');  
}, 3000);  
</script>  
<style>  
#content{  
background-color:#00A1E0;  
font-size:24px;  
font-weight:bold;  
padding-top:10px;  
color:#fff;  
min-height: 200px;  
}  
#content,h1{  
     text-align: center;  
}  
</style>  
<title>Auto Load Page in Div using Jquery</title>  
</head>  
<body>  
<h1>Auto Load Page in Div</h1>  
<div id="content"> Please wait .. </div>  
</body>  
<html> 