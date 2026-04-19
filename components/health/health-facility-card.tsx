import { cn } from "@/lib/utils"
import { MapPin, Star, Building2, Pill, Stethoscope } from "lucide-react"
import Link from "next/link"

export interface HealthFacility {
  id: string
  name: string
  type: "farmacia" | "hospital" | "posto"
  address: string
  rating: number
  reviews: string
  distance?: string
  status: "open" | "24h" | "closing-soon" | "closed"
  featured?: boolean
}

interface HealthFacilityCardProps {
  facility: HealthFacility
  className?: string
}

const statusLabels = {
  open: { label: "Aberto", className: "bg-tertiary-fixed text-on-tertiary-fixed" },
  "24h": { label: "24 Horas", className: "bg-tertiary-fixed text-on-tertiary-fixed" },
  "closing-soon": { label: "Fecha em 1h", className: "bg-muted text-muted-foreground" },
  closed: { label: "Fechado", className: "bg-destructive/10 text-destructive" },
}

const typeConfig = {
  farmacia: { 
    label: "Farmacia", 
    icon: Pill, 
    className: "bg-blue-100 text-blue-700 dark:bg-blue-900/30 dark:text-blue-300" 
  },
  hospital: { 
    label: "Hospital", 
    icon: Building2, 
    className: "bg-red-100 text-red-700 dark:bg-red-900/30 dark:text-red-300" 
  },
  posto: { 
    label: "Posto Medico", 
    icon: Stethoscope, 
    className: "bg-green-100 text-green-700 dark:bg-green-900/30 dark:text-green-300" 
  },
}

export function HealthFacilityCard({ facility, className }: HealthFacilityCardProps) {
  const status = statusLabels[facility.status]
  const typeInfo = typeConfig[facility.type]
  const TypeIcon = typeInfo.icon

  return (
    <Link
      href={`/instituicao/${facility.id}`}
      className={cn(
        "bg-card p-5 rounded-2xl shadow-sm hover:shadow-md transition-shadow group cursor-pointer block",
        facility.featured && "border-l-4 border-primary",
        className
      )}
    >
      <div className="flex justify-between items-start mb-3">
        <div className="space-y-1 flex-1">
          <div className="flex items-center gap-2 mb-1">
            <span className={cn("px-2 py-0.5 rounded text-[10px] font-bold uppercase flex items-center gap-1", typeInfo.className)}>
              <TypeIcon className="w-3 h-3" />
              {typeInfo.label}
            </span>
          </div>
          <h3 className="font-bold text-primary group-hover:text-primary/80 transition-colors">
            {facility.name}
          </h3>
          <p className="text-xs text-muted-foreground flex items-center gap-1">
            <MapPin className="w-3.5 h-3.5" />
            {facility.address}
          </p>
        </div>
        <span className={cn("px-2 py-1 rounded text-[10px] font-bold uppercase shrink-0", status.className)}>
          {status.label}
        </span>
      </div>
      
      <div className="flex items-center justify-between mt-4">
        <div className="flex items-center gap-1">
          <Star className="w-4 h-4 text-tertiary fill-tertiary" />
          <span className="text-xs font-bold">{facility.rating}</span>
          <span className="text-[10px] text-muted-foreground">({facility.reviews})</span>
        </div>
        {facility.distance && (
          <span className="text-sm font-bold text-primary">
            {facility.distance}
          </span>
        )}
      </div>
    </Link>
  )
}
