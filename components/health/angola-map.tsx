"use client"

import dynamic from "next/dynamic"
import { type HealthFacility } from "./health-facility-card"

// Dynamic import of the real Leaflet map to prevent SSR issues
const AngolaMapInner = dynamic(() => import("./angola-map-inner"), {
  ssr: false,
  loading: () => (
    <div className="flex-1 min-h-[400px] w-full bg-slate-100 flex items-center justify-center rounded-xl overflow-hidden relative">
      <div className="absolute z-10 flex flex-col items-center gap-3">
        <div className="w-8 h-8 border-4 border-primary border-t-transparent rounded-full animate-spin"></div>
        <span className="text-slate-600 font-medium text-sm">A carregar mapa interativo...</span>
      </div>
    </div>
  ),
})

export interface AngolaMapProps {
  facilities?: HealthFacility[]
  isFullscreen?: boolean
  onExitFullscreen?: () => void
  onEnterFullscreen?: () => void
}

export function AngolaMap(props: AngolaMapProps) {
  return <AngolaMapInner {...props} />
}