var MINI = require('minified'); 
var $ = MINI.$, HTML = MINI.HTML;

$(function(){

	function ValidateIPaddress(inputText) {
	    var ipformat = /^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/;
	    return inputText.match(ipformat);
	}

	$('#buttonChangeIp').click(function(){
		var ip = $('#boxIp').val();

		if(!ip){
			$.notify("Preencha todos os campos", "error");
			return;
		}

		else if(!ValidateIPaddress(ip)){
			$.notify("Formato de IP inválido", "error");
			return;
		}

		var args = btoa(ip);
		var urlData = "[4;" +  args + "]";

		$.ajax({
            type: "GET",
            url: "/",
            async: true,
            data: urlData,

            success: function(data) { 

            	var d = data.split(":");

				if(d[1] == 1){
					$.notify("Clique em aplicar modificações para completar", "warn");                
					$.notify("IP alterado com sucesso", "success");  
					$('#changeIp').modal('hide');
					$('#boxIp').val('');  						
				}  				
				else{
					$.notify("Não foi possível alterar o IP", "error");
				}
            },
        });
	});

	$('#buttonChangeGateway').click(function(){
		var gat = $('#boxGateway').val();

		if(!gat){
			$.notify("Preencha todos os campos", "error");
			return;
		}

		else if(!ValidateIPaddress(gat)){
			$.notify("Formato de gateway inválido", "error");
			return;
		}

		var args = btoa(gat);
		var urlData = "[5;" +  args + "]";

		$.ajax({
            type: "GET",
            url: "/",
            async: true,
            data: urlData,

            success: function(data) { 

            	var d = data.split(":");

				if(d[1] == 1){
					$.notify("Clique em aplicar modificações para completar", "warn");                
					$.notify("Gateway alterado com sucesso", "success");  
					$('#changeGateway').modal('hide');
					$('#boxGateway').val('');  						
				}  				
				else{
					$.notify("Não foi possível alterar gateway", "error");
				}
            },
        });
	});

	$('#buttonChangeSubNetwork').click(function(){
		var gat = $('#boxSubNetwork').val();

		if(!gat){
			$.notify("Preencha todos os campos", "error");
			return;
		}

		else if(!ValidateIPaddress(gat)){
			$.notify("Formato de máscara de sub rede inválido", "error");
			return;
		}

		var args = btoa(gat);
		var urlData = "[6;" +  args + "]";

		$.ajax({
            type: "GET",
            url: "/",
            async: true,
            data: urlData,

            success: function(data) { 

            	var d = data.split(":");

				if(d[1] == 1){
					$.notify("Clique em aplicar modificações para completar", "warn");                
					$.notify("Máscara de sub rede alterado com sucesso", "success");         
					$('#changeSubNetwork').modal('hide');
					$('#boxSubNetwork').val('');  						
				}  				
				else{
					$.notify("Não foi possível alterar a máscara de sub rede", "error");
				}
            },
        });
	});

	$('#buttonChangePass').click(function(){

		var oldPass = $('#boxOldPass').val();
		var newPass1 = $('#boxNewPass1').val();
		var newPass2 = $('#boxNewPass2').val();

		if(!oldPass || !newPass1 || !newPass2){
			$.notify("Preencha todos os campos", "error");
			return;
		}

		else if(newPass1 != newPass2){
			$.notify("As senhas são diferentes", "error");
			return;
		}

		if(newPass1.length < 4 || newPass1.length > 16){
			$.notify("A senha deve ter entre 4 e 16 caracteres", "error");
			return;
		}

		//encode: btoa
		//decode: atob

		var args = btoa(oldPass + ";" + newPass1 + ";" + newPass2);
		var urlData = "[7;" +  args + "]";

		$.ajax({
            type: "GET",
            url: "/",
            async: true,
            data: urlData,

            success: function(data) { 	

            	var d = data.split(":");

				if(d[1] == 1){
					$.notify("Senha alterada com sucesso", "success");

					$('#changePass').modal('hide');

					$('#boxOldPass').val('');
					$('#boxNewPass1').val('');
					$('#boxNewPass2').val('');
				}            	
				else{
					$.notify("Senha informada incorreta", "error");
				}
            }
        });
	});
	
	$('ul.navbar-left li.restart-all').click(function(e){
		waitingDialog.show("Reiniciando");

		var urlData = "[1]";
		var success = false;

		$.ajax({
            type: "GET",
            url: "/",
            async: true,
            data: urlData,

            success: function(data) { 	

            	var d = data.split(":");

				if(d[1] == 1){
					success = true;	
				}            	
            }
        });

		setTimeout(function () {

			urlData = "[2]";
			success = false;

			$.ajax({
	            type: "GET",
	            url: "/",
	            async: true,
	            data: urlData,

	            success: function(data) { 	

	            	var d = data.split(":");

					if(d[1] == 1){
						success = true;	
					}            	
	            }
	        });

			waitingDialog.hide();

			window.location = '/';
		}, 5000)		
	});
})

