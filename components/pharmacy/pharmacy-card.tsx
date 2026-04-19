import { cn } from "@/lib/utils"
import { MapPin, Star } from "lucide-react"
import Link from "next/link"

export interface Pharmacy {
  id: string
  name: string
  address: string
  rating: number
  reviews: string
  deliveryFee: string
  status: "open" | "24h" | "closing-soon" | "closed"
  distance?: string
  featured?: boolean
}

interface PharmacyCardProps {
  pharmacy: Pharmacy
  className?: string
}

const statusLabels = {
  open: { label: "Aberto", className: "bg-tertiary-fixed text-on-tertiary-fixed" },
  "24h": { label: "24 Horas", className: "bg-tertiary-fixed text-on-tertiary-fixed" },
  "closing-soon": { label: "Fecha em 1h", className: "bg-muted text-muted-foreground" },
  closed: { label: "Fechado", className: "bg-destructive/10 text-destructive" },
}

export function PharmacyCard({ pharmacy, className }: PharmacyCardProps) {
  const status = statusLabels[pharmacy.status]

  return (
    <Link
      href={`/farmacias/${pharmacy.id}`}
      className={cn(
        "bg-card p-5 rounded-2xl shadow-sm hover:shadow-md transition-shadow group cursor-pointer block",
        pharmacy.featured && "border-l-4 border-primary",
        className
      )}
    >
      <div className="flex justify-between items-start mb-3">
        <div className="space-y-1">
          <h3 className="font-bold text-primary group-hover:text-primary/80 transition-colors">
            {pharmacy.name}
          </h3>
          <p className="text-xs text-muted-foreground flex items-center gap-1">
            <MapPin className="w-3.5 h-3.5" />
            {pharmacy.address}
          </p>
        </div>
        <span className={cn("px-2 py-1 rounded text-[10px] font-bold uppercase", status.className)}>
          {status.label}
        </span>
      </div>
      
      <div className="flex items-center justify-between mt-4">
        <div className="flex items-center gap-1">
          <Star className="w-4 h-4 text-tertiary fill-tertiary" />
          <span className="text-xs font-bold">{pharmacy.rating}</span>
          <span className="text-[10px] text-muted-foreground">({pharmacy.reviews})</span>
        </div>
        <span className="text-sm font-bold text-primary">
          {pharmacy.deliveryFee}{" "}
          <span className="text-[10px] font-medium text-muted-foreground">
            {pharmacy.deliveryFee === "Gratis" ? "entrega" : "taxa de entrega"}
          </span>
        </span>
      </div>
    </Link>
  )
}
