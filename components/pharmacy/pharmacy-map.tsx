"use client"

import { Pill, Plus, Minus, LocateFixed, Truck } from "lucide-react"
import { Button } from "@/components/ui/button"

interface MapMarker {
  id: string
  name: string
  position: { top: string; left: string }
  highlighted?: boolean
}

interface PharmacyMapProps {
  markers?: MapMarker[]
}

const defaultMarkers: MapMarker[] = [
  { id: "1", name: "Farmácia Welwitschia", position: { top: "33%", left: "25%" }, highlighted: true },
  { id: "2", name: "Apothecary Maianga", position: { top: "50%", left: "66%" } },
]

export function PharmacyMap({ markers = defaultMarkers }: PharmacyMapProps) {
  return (
    <section className="flex-1 relative bg-muted">
      {/* Map Background */}
      <div className="absolute inset-0 z-0">
        <img
          src="https://images.unsplash.com/photo-1524661135-423995f22d0b?w=1200&h=800&fit=crop"
          alt="Mapa de Luanda"
          className="w-full h-full object-cover filter contrast-75 brightness-110"
        />
      </div>

      {/* Map Controls */}
      <div className="absolute top-6 right-6 flex flex-col gap-3 z-30">
        <div className="bg-white/70 backdrop-blur-xl p-2 rounded-2xl shadow-lg border border-white/20 flex flex-col gap-2">
          <button className="w-10 h-10 flex items-center justify-center hover:bg-white rounded-xl transition-colors">
            <Plus className="w-5 h-5" />
          </button>
          <div className="h-[1px] bg-slate-200/50 mx-2" />
          <button className="w-10 h-10 flex items-center justify-center hover:bg-white rounded-xl transition-colors">
            <Minus className="w-5 h-5" />
          </button>
        </div>
        <button className="w-12 h-12 bg-primary text-primary-foreground rounded-full shadow-lg flex items-center justify-center hover:scale-105 transition-transform">
          <LocateFixed className="w-5 h-5" />
        </button>
      </div>

      {/* Map Markers */}
      {markers.map((marker) => (
        <div
          key={marker.id}
          className="absolute z-30 group cursor-pointer"
          style={{ top: marker.position.top, left: marker.position.left }}
        >
          <div className="relative">
            <div className={`${marker.highlighted ? "bg-primary animate-bounce" : "bg-primary/80"} text-white p-3 rounded-full shadow-xl`}>
              <Pill className="w-5 h-5" />
            </div>
            <div className="absolute -bottom-8 left-1/2 -translate-x-1/2 whitespace-nowrap bg-white px-3 py-1 rounded-full shadow-md border border-slate-100 hidden group-hover:block">
              <span className="text-xs font-bold text-primary">{marker.name}</span>
            </div>
          </div>
        </div>
      ))}

      {/* Info Overlay Card */}
      <div className="absolute bottom-10 left-10 right-10 md:left-auto md:right-10 md:w-80 z-30">
        <div className="bg-white/80 backdrop-blur-2xl p-6 rounded-[2rem] shadow-lg border border-white/30 space-y-4">
          <div className="flex items-center gap-4">
            <div className="w-12 h-12 rounded-2xl bg-secondary flex items-center justify-center">
              <Truck className="w-6 h-6 text-primary" />
            </div>
            <div>
              <h4 className="text-sm font-bold text-foreground leading-tight">Entrega Rápida em Luanda</h4>
              <p className="text-xs text-muted-foreground">Tempo médio: 45 min</p>
            </div>
          </div>
          <p className="text-xs text-muted-foreground leading-relaxed">
            Encontramos <strong>14 farmácias</strong> disponíveis para entrega imediata na sua zona atual.
          </p>
          <Button className="w-full rounded-2xl py-6 font-bold shadow-lg">
            Ver Lista Completa
          </Button>
        </div>
      </div>
    </section>
  )
}
