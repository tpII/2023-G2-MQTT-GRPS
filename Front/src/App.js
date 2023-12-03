import React from 'react'
import HookMqtt from './components/Hook/'
import TemperaturesChart from './components/Grafico'
// Hook or Class
// import ClassMqtt from './components/Class/'
import './App.css'

function App() {

  return (
    <div className="App">
      <HookMqtt />
      <TemperaturesChart />
    </div>
  )
}

export default App
