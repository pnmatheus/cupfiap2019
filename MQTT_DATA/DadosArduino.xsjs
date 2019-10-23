$.response.contentType = "application/json";


function grava_dados()
{
	var output = [];
	var log = {};
	var sql = null;
	var pstmt = null;
	
try {
    var conn = $.db.getConnection();
    	
    //var id = String(Math.floor((Math.random() * 1000) + 1));
    var referencia = $.request.parameters.get('referencia');
    var distancia = $.request.parameters.get('distancia');
    var nivel = $.request.parameters.get('nivel');
    var umidade = $.request.parameters.get('umidade_percentual');
    var timestamp = $.request.parameters.get('timestamp');
    
    sql = "INSERT INTO \"SYSTEM\".\"MQTT_DATA\" (REFERENCIA, DISTANCIA, NIVEL, UMIDADE_PERCENTUAL, TIMESTAMP) VALUES(?,?,?,?,?)";
	pstmt = conn.prepareStatement(sql);
	
	//pstmt.setString(1,id);
	pstmt.setString(1,referencia);
	pstmt.setString(2,distancia);
	pstmt.setString(3,nivel);
	pstmt.setString(4,umidade);
	pstmt.setString(5,timestamp);
			
	pstmt.execute();
			
	pstmt.close();
    conn.commit();
		    
conn.close();

log.response = "Dados Gravados com sucesso!";
output.push(log);

$.response.setBody(JSON.stringify(output));

}catch (error){
	log.response = "Falha de gravacao dos dados...";
	output.push(log);
	
    $.response.setBody (JSON.stringify(output.response + error));
    $.response.status = $.net.http.INTERNAL_SERVER_ERROR;

}

}


grava_dados();

