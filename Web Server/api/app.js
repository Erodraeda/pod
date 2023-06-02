const path = require('path')
const express = require('express')
const parser = require('body-parser')
const dotenv = require('dotenv')
dotenv.config()

const app = express()

app.use(parser.urlencoded({ extended: true }))
app.use(parser.json())
app.disable('x-powered-by')

const Pools = require('./pools')

app
    .get('/', async (req, res) => {

        console.log('[GET] / - get all servers')

        try {

            const servers = await Pools.getServers()
    
            res.json({servers})

        } catch (error) {
            console.error(`failed to get servers - ${error}`)
            res.status(500).json(error)
        }
    })
    .get('/get/:serverId', async (req, res) => {

        const {serverId} = req.params

        console.log(`[GET] /get/${serverId} - get specific server`)

        try {

            let servers = await Pools.getServer(serverId)

            if (servers.length == 0) servers = 'No such server found!'
    
            res.json({servers})

        } catch (error) {
            console.error(`failed to get servers - ${error}`)
            res.status(500).json(error)
        }
    })
    .post('/add/:serverName', async (req, res) => {

        const {serverName} = req.params

        console.log(`[POST] /add/${serverName} - add a new server`)

        try {

            const servers = await Pools.addServer(serverName)

            const insertId = servers.insertId + ''

            const success = `Successfuly added new server: ${serverName} with id: ${insertId}`
    
            res.json({insertId})

        } catch (error) {
            console.error(`failed to get servers - ${error}`)
            res.status(500).json(error)
        }
    })
    .post('/delete/:serverId', async (req, res) => {

        const {serverId} = req.params

        console.log(`[POST] /delete/${serverId} - deletes an existing server`)

        try {

            const servers = await Pools.delServer(serverId)

            const affectedRows = servers.affectedRows

            const success = `Successfuly deleted ${serverId}`
    
            res.json({affectedRows, success})

        } catch (error) {
            console.error(`failed to get servers - ${error}`)
            res.status(500).json(error)
        }
    })
    .post('/update/:serverId/:serverName', async (req, res) => {

        const {serverId, serverName} = req.params

        console.log(`[POST] /update/${serverId}/${serverName} - update a server name`)

        try {

            const servers = await Pools.updServer(serverId, serverName)

            const affectedRows = servers.affectedRows

            const success = `Successfuly updated ${serverId} to ${serverName}`
    
            res.json({affectedRows, success})

        } catch (error) {
            console.error(`failed to get servers - ${error}`)
            res.status(500).json(error)
        }
    })

const port = process.env.PORT || 3000

app.listen(port, () => console.log(`App listening on port ${port}!`))
module.exports = app
