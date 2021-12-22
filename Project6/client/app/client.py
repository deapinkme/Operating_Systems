express = require('express')

app = express()

app.get('/'. (req, res) => res.send('Hello a'))

app.listen(5000, () => console.log('Listening on 5000 *make sure this is container or localport*'))