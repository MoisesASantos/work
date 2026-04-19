"use client"

import { Building2, Plus, Minus, LocateFixed, Pill, Stethoscope, Navigation, Maximize2, Minimize2, X, Layers } from "lucide-react"
import { type HealthFacility } from "./health-facility-card"
import Link from "next/link"
import { useState } from "react"
import { Button } from "@/components/ui/button"

interface AngolaMapProps {
  facilities?: HealthFacility[]
  isFullscreen?: boolean
  onExitFullscreen?: () => void
  onEnterFullscreen?: () => void
}

const typeIcons = {
  farmacia: Pill,
  hospital: Building2,
  posto: Stethoscope,
}

const typeColors = {
  farmacia: "bg-blue-600",
  hospital: "bg-red-600",
  posto: "bg-green-600",
}

// Posicoes simuladas para marcadores em Luanda - estilo mapa
const markerPositions: Record<string, { top: string; left: string }> = {
  welwitschia: { top: "42%", left: "58%" },
  maianga: { top: "35%", left: "45%" },
  "hospital-militar": { top: "38%", left: "52%" },
  "centro-saude-cazenga": { top: "30%", left: "62%" },
  "clinica-sagrada": { top: "55%", left: "65%" },
  "farmacia-central": { top: "40%", left: "40%" },
  "posto-viana": { top: "60%", left: "72%" },
}

export function AngolaMap({ facilities = [], isFullscreen = false, onExitFullscreen, onEnterFullscreen }: AngolaMapProps) {
  const [mapStyle, setMapStyle] = useState<"streets" | "satellite">("streets")
  const [showLegend, setShowLegend] = useState(true)

  return (
    <section className={`flex-1 relative bg-slate-100 ${isFullscreen ? "fixed inset-0 z-50" : ""}`}>
      {/* Map Background - Street style (Google Maps like) */}
      <div className="absolute inset-0 z-0">
        {mapStyle === "streets" ? (
          <>
            {/* Street map style background */}
            <div className="w-full h-full bg-[#e8e4d8]">
              {/* Simulated roads and streets */}
              <svg className="w-full h-full" viewBox="0 0 100 100" preserveAspectRatio="none">
                {/* Water/Ocean */}
                <rect x="0" y="0" width="30" height="100" fill="#a3c4dc" />
                <path d="M30 0 Q 35 30, 28 50 Q 22 70, 30 100 L0 100 L0 0 Z" fill="#a3c4dc" />
                
                {/* Main roads */}
                <line x1="30" y1="50" x2="100" y2="50" stroke="#ffffff" strokeWidth="1.5" />
                <line x1="50" y1="0" x2="50" y2="100" stroke="#ffffff" strokeWidth="1.5" />
                <line x1="70" y1="0" x2="70" y2="100" stroke="#ffffff" strokeWidth="1" />
                <line x1="30" y1="30" x2="100" y2="30" stroke="#ffffff" strokeWidth="1" />
                <line x1="30" y1="70" x2="100" y2="70" stroke="#ffffff" strokeWidth="1" />
                
                {/* Secondary roads */}
                <line x1="40" y1="20" x2="40" y2="80" stroke="#ffffff" strokeWidth="0.5" />
                <line x1="60" y1="20" x2="60" y2="80" stroke="#ffffff" strokeWidth="0.5" />
                <line x1="80" y1="20" x2="80" y2="80" stroke="#ffffff" strokeWidth="0.5" />
                <line x1="35" y1="40" x2="95" y2="40" stroke="#ffffff" strokeWidth="0.5" />
                <line x1="35" y1="60" x2="95" y2="60" stroke="#ffffff" strokeWidth="0.5" />
                
                {/* Green areas / parks */}
                <rect x="42" y="55" width="8" height="10" rx="1" fill="#c5e1a5" />
                <rect x="72" y="35" width="12" height="8" rx="1" fill="#c5e1a5" />
                <circle cx="55" cy="25" r="4" fill="#c5e1a5" />
                
                {/* Buildings blocks */}
                <rect x="35" y="32" width="4" height="6" fill="#d1c4b0" />
                <rect x="45" y="32" width="3" height="5" fill="#d1c4b0" />
                <rect x="52" y="52" width="5" height="6" fill="#d1c4b0" />
                <rect x="62" y="42" width="6" height="5" fill="#d1c4b0" />
                <rect x="75" y="52" width="8" height="10" fill="#d1c4b0" />
                <rect x="85" y="25" width="6" height="8" fill="#d1c4b0" />
              </svg>
            </div>
            {/* Road labels */}
            <div className="absolute top-[48%] left-[60%] text-[8px] text-slate-500 font-medium tracking-wider transform -rotate-0">
              AV. 21 DE JANEIRO
            </div>
            <div className="absolute top-[28%] left-[48%] text-[8px] text-slate-500 font-medium tracking-wider transform rotate-90">
              RUA DO MAT
            </div>
          </>
        ) : (
          <>
            {/* Satellite view */}
            <img
              src="https://images.unsplash.com/photo-1569336415962-a4bd9f69cd83?w=1600&h=1000&fit=crop"
              alt="Mapa Satelite de Luanda"
              className="w-full h-full object-cover"
            />
            <div className="absolute inset-0 bg-slate-900/20" />
          </>
        )}
      </div>

      {/* Fullscreen Exit Button */}
      {isFullscreen && (
        <button
          onClick={onExitFullscreen}
          className="absolute top-4 left-4 z-50 bg-white shadow-lg rounded-xl p-3 hover:bg-slate-50 transition-colors"
        >
          <X className="w-5 h-5" />
        </button>
      )}

      {/* Map Controls */}
      <div className="absolute top-4 right-4 flex flex-col gap-2 z-30">
        {/* Map Style Toggle */}
        <div className="bg-white shadow-lg rounded-xl overflow-hidden">
          <button 
            onClick={() => setMapStyle("streets")}
            className={`w-full px-3 py-2 text-xs font-medium flex items-center gap-2 transition-colors ${
              mapStyle === "streets" ? "bg-primary text-white" : "hover:bg-slate-50"
            }`}
          >
            <Layers className="w-4 h-4" />
            Mapa
          </button>
          <button 
            onClick={() => setMapStyle("satellite")}
            className={`w-full px-3 py-2 text-xs font-medium flex items-center gap-2 transition-colors ${
              mapStyle === "satellite" ? "bg-primary text-white" : "hover:bg-slate-50"
            }`}
          >
            <Layers className="w-4 h-4" />
            Satelite
          </button>
        </div>

        {/* Zoom Controls */}
        <div className="bg-white shadow-lg p-1 rounded-xl flex flex-col gap-1">
          <button className="w-9 h-9 flex items-center justify-center hover:bg-slate-100 rounded-lg transition-colors">
            <Plus className="w-4 h-4" />
          </button>
          <div className="h-[1px] bg-slate-200 mx-2" />
          <button className="w-9 h-9 flex items-center justify-center hover:bg-slate-100 rounded-lg transition-colors">
            <Minus className="w-4 h-4" />
          </button>
        </div>

        {/* Location Button */}
        <button className="w-11 h-11 bg-white shadow-lg text-primary rounded-xl flex items-center justify-center hover:bg-slate-50 transition-colors">
          <LocateFixed className="w-5 h-5" />
        </button>

        {/* Fullscreen Toggle */}
        {!isFullscreen && onEnterFullscreen && (
          <button 
            onClick={onEnterFullscreen}
            className="w-11 h-11 bg-white shadow-lg rounded-xl flex items-center justify-center hover:bg-slate-50 transition-colors"
          >
            <Maximize2 className="w-5 h-5" />
          </button>
        )}
        {isFullscreen && (
          <button 
            onClick={onExitFullscreen}
            className="w-11 h-11 bg-white shadow-lg rounded-xl flex items-center justify-center hover:bg-slate-50 transition-colors"
          >
            <Minimize2 className="w-5 h-5" />
          </button>
        )}
      </div>

      {/* User Location Marker */}
      <div 
        className="absolute z-40"
        style={{ top: "45%", left: "50%" }}
      >
        <div className="relative">
          <div className="w-5 h-5 bg-blue-500 rounded-full border-3 border-white shadow-lg" />
          <div className="absolute -inset-3 bg-blue-500/20 rounded-full animate-ping" />
          <div className="absolute -inset-6 bg-blue-500/10 rounded-full" />
        </div>
      </div>

      {/* Facility Markers */}
      {facilities.map((facility) => {
        const position = markerPositions[facility.id] || { top: "50%", left: "50%" }
        const Icon = typeIcons[facility.type]
        const bgColor = typeColors[facility.type]
        
        return (
          <Link
            key={facility.id}
            href={`/instituicao/${facility.id}`}
            className="absolute z-30 group cursor-pointer"
            style={{ top: position.top, left: position.left }}
          >
            <div className="relative">
              {/* Marker pin shape */}
              <div className={`${bgColor} text-white p-2 rounded-full shadow-lg hover:scale-110 transition-transform ring-2 ring-white`}>
                <Icon className="w-4 h-4" />
              </div>
              {/* Pin point */}
              <div className={`absolute -bottom-1 left-1/2 -translate-x-1/2 w-2 h-2 ${bgColor} rotate-45`} />
              
              {/* Tooltip */}
              <div className="absolute -bottom-14 left-1/2 -translate-x-1/2 whitespace-nowrap bg-white px-3 py-2 rounded-lg shadow-lg border border-slate-100 hidden group-hover:block min-w-[140px]">
                <span className="text-xs font-bold text-slate-900 block">{facility.name}</span>
                <div className="flex items-center gap-2 mt-1">
                  <span className="text-[10px] text-slate-500">{facility.distance}</span>
                  <span className="text-[10px] text-primary font-medium">Ver direcoes</span>
                </div>
              </div>
            </div>
          </Link>
        )
      })}

      {/* Legend - Collapsible */}
      <div className={`absolute bottom-4 left-4 z-30 transition-all ${isFullscreen ? "bottom-6 left-6" : ""}`}>
        {showLegend ? (
          <div className="bg-white/95 backdrop-blur p-4 rounded-xl shadow-lg border border-slate-100 max-w-[180px]">
            <div className="flex items-center justify-between mb-3">
              <h4 className="text-xs font-bold text-slate-900 uppercase tracking-wider">Legenda</h4>
              <button 
                onClick={() => setShowLegend(false)}
                className="text-slate-400 hover:text-slate-600"
              >
                <X className="w-3.5 h-3.5" />
              </button>
            </div>
            <div className="space-y-2">
              <div className="flex items-center gap-2">
                <div className="w-6 h-6 bg-blue-600 rounded-full flex items-center justify-center ring-2 ring-white shadow">
                  <Pill className="w-3 h-3 text-white" />
                </div>
                <span className="text-xs text-slate-700">Farmacia</span>
              </div>
              <div className="flex items-center gap-2">
                <div className="w-6 h-6 bg-red-600 rounded-full flex items-center justify-center ring-2 ring-white shadow">
                  <Building2 className="w-3 h-3 text-white" />
                </div>
                <span className="text-xs text-slate-700">Hospital</span>
              </div>
              <div className="flex items-center gap-2">
                <div className="w-6 h-6 bg-green-600 rounded-full flex items-center justify-center ring-2 ring-white shadow">
                  <Stethoscope className="w-3 h-3 text-white" />
                </div>
                <span className="text-xs text-slate-700">Posto Medico</span>
              </div>
              <div className="flex items-center gap-2">
                <div className="w-5 h-5 bg-blue-500 rounded-full border-2 border-white shadow" />
                <span className="text-xs text-slate-700">Voce esta aqui</span>
              </div>
            </div>
          </div>
        ) : (
          <button 
            onClick={() => setShowLegend(true)}
            className="bg-white shadow-lg px-3 py-2 rounded-xl text-xs font-medium hover:bg-slate-50 transition-colors"
          >
            Mostrar legenda
          </button>
        )}
      </div>

      {/* Info Overlay Card */}
      <div className={`absolute bottom-4 right-4 w-72 z-30 ${isFullscreen ? "bottom-6 right-6" : ""}`}>
        <div className="bg-white/95 backdrop-blur p-4 rounded-xl shadow-lg border border-slate-100 space-y-3">
          <div className="flex items-center gap-3">
            <div className="w-10 h-10 rounded-xl bg-primary/10 flex items-center justify-center">
              <Navigation className="w-5 h-5 text-primary" />
            </div>
            <div>
              <h4 className="text-sm font-bold text-slate-900 leading-tight">Talatona, Luanda</h4>
              <p className="text-xs text-slate-500">Sua localizacao atual</p>
            </div>
          </div>
          <p className="text-xs text-slate-600 leading-relaxed">
            <strong className="text-primary">{facilities.length}</strong> instituicoes de saude encontradas nesta area.
          </p>
          {isFullscreen && (
            <Button 
              variant="outline" 
              size="sm" 
              className="w-full text-xs"
              onClick={onExitFullscreen}
            >
              Voltar a lista
            </Button>
          )}
        </div>
      </div>
    </section>
  )
}
