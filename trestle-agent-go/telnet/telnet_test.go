package trestle_telnet_test

import (
	"testing"

	tel "github.com/kenneththompson/trestle/trestle-agent-go/telnet"
)

func TestTelnet(t *testing.T) {
	//tel.Telnet_Launch()
	tel.TelnetServer.Start()

	//log.Printf(" [*] Waiting for messages. To exit press CTRL+C")
	//var handler telnet.Handler = telnet.EchoHandler

	//err := telnet.ListenAndServe("localhost:5555", handler)
	//if nil != err {
	//@TODO: Handle this error better.
	//	panic(err)
	//}
}
