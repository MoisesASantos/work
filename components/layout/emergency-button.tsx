"use client"

import { Phone } from "lucide-react"
import Link from "next/link"

export function EmergencyButton() {
  return (
    <Link
      href="tel:112"
      className="fixed right-4 bottom-28 md:bottom-6 z-50 group"
      aria-label="Emergencia - Ligar 112"
    >
      <div className="relative">
        {/* Pulse ring */}
        <div className="absolute inset-0 rounded-full bg-red-500 animate-ping opacity-30" />
        
        {/* Button */}
        <div className="relative flex items-center gap-2 bg-gradient-to-r from-red-600 to-red-500 text-white px-4 py-3 rounded-full shadow-lg shadow-red-500/30 hover:shadow-red-500/50 hover:scale-105 transition-all duration-200">
          <div className="w-8 h-8 bg-white/20 rounded-full flex items-center justify-center">
            <Phone className="w-4 h-4" />
          </div>
          <div className="pr-1">
            <p className="text-xs font-bold uppercase tracking-wider">Emergencia</p>
            <p className="text-[10px] opacity-80">Ligar 112</p>
          </div>
        </div>
      </div>
    </Link>
  )
}
