"use client"

import { Phone, Bot } from "lucide-react"
import Link from "next/link"

export function EmergencyButton() {
  return (
    <div className="fixed right-4 bottom-24 md:bottom-6 z-50 flex flex-col items-end gap-3">
      {/* Botão do Agente IA */}
      <Link
        href="/suporte"
        className="group relative flex items-center justify-center bg-gradient-to-r from-primary to-primary/80 text-primary-foreground w-12 h-12 md:w-14 md:h-14 rounded-full shadow-xl shadow-primary/30 hover:shadow-primary/50 hover:scale-105 transition-all duration-200"
        aria-label="Fale com a Assistente IA"
      >
        <Bot className="w-6 h-6 md:w-7 md:h-7 text-white" />
      </Link>

      {/* Botão de Emergência */}
      <Link
        href="tel:112"
        className="group relative"
        aria-label="Emergência - Ligar 112"
      >
        <div className="relative">
          {/* Pulse ring */}
          <div className="absolute inset-0 rounded-full bg-destructive animate-ping opacity-30" />
          
          {/* Button */}
          <div className="relative flex items-center justify-center bg-gradient-to-r from-destructive to-destructive/80 text-destructive-foreground w-12 h-12 md:w-14 md:h-14 rounded-full shadow-xl shadow-destructive/30 hover:shadow-destructive/50 hover:scale-105 transition-all duration-200">
            <Phone className="w-5 h-5 md:w-6 md:h-6 text-white" />
          </div>
        </div>
      </Link>
    </div>
  )
}
