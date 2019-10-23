function doGet() {
	var attendanceID2 = $.request.body.asString();
	//var essai = attendanceID2.toString().replace("\r", "").replace("\n", "").replace("\t", "");
	//essai = JSON.parse(essai);
	//var evento=essai.evento;
	var essai = JSON.parse(attendanceID2);
    var id = essai.id;
	var output;
	var body;
	var resultSet = null;
	var results = [];
	var result;
	var columnCount;
	var columnName;

	var dbQuery = 'SELECT *FROM "SYSTEM"."MQTT_DATA" WHERE "ID"=' + "'" + id.toString() + "'";

	var connection = $.db.getConnection();
	var statement = null;
	statement = connection.prepareStatement(dbQuery);
	resultSet = statement.executeQuery();
	while (resultSet.next()) {
		result = {};
		columnCount = resultSet.getMetaData().getColumnCount();

		for (var i = 0; i < columnCount; i++) {
			columnName = resultSet.getMetaData().getColumnName(i + 1);
			result[columnName] = resultSet.getNString(i + 1);
		}
		results.push(result);
	}
	//output = results[0];
	output = {
		replies: [{
			type: 'text',
			content: "Referencia : "+results[0].REFERENCIA +
			"\nDistancia : "+results[0].DISTANCIA + 
			"\nNivel : "+results[0].NIVEL + 
			"\nUmidade : "+results[0].UMIDADE_PERCENTUAL +
			"\nData e Hora : "+results[0].TIMESTAMP
                                }],
		conversation: {
			memory: results[0]
		}
	};

	var output2 = {
		"replies": [
			{
				"type": "text",
				"content": results[0]
    }
  ],
		"conversation": {
			"language": "pt",
			"memory": {
				"user": "Bob"
			}
		}
	};
	body = JSON.stringify(output);
	$.response.contentType = 'application/json';
	$.response.setBody(body);
	$.response.status = $.net.http.OK;

}
doGet();