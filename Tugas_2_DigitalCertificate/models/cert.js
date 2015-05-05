var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var certSchema = new Schema({
	certificate : String,
	user : Schema.ObjectId
});

mongoose.model('cert', certSchema);
