import { cn } from "@/lib/utils"
import { CheckCircle2, Lock, Plus } from "lucide-react"

export interface Medicine {
  id: string
  name: string
  description: string
  price: number
  image: string
  inStock: boolean
  requiresPrescription?: boolean
  featured?: boolean
  featuredLabel?: string
  featuredDescription?: string
}

interface MedicineCardProps {
  medicine: Medicine
  onAdd?: (id: string) => void
  className?: string
}

export function MedicineCard({ medicine, onAdd, className }: MedicineCardProps) {
  if (medicine.featured) {
    return (
      <div className={cn("bg-primary md:col-span-2 p-6 rounded-3xl relative overflow-hidden flex items-center gap-8", className)}>
        <div className="absolute top-0 right-0 p-4 opacity-10">
          <svg className="w-24 h-24" fill="currentColor" viewBox="0 0 24 24">
            <path d="M19 3H5c-1.1 0-2 .9-2 2v14c0 1.1.9 2 2 2h14c1.1 0 2-.9 2-2V5c0-1.1-.9-2-2-2zm-7 14c-3.31 0-6-2.69-6-6s2.69-6 6-6 6 2.69 6 6-2.69 6-6 6z" />
          </svg>
        </div>
        <div className="w-32 h-32 rounded-2xl bg-white/20 backdrop-blur-xl overflow-hidden shrink-0 p-2">
          <img
            src={medicine.image}
            alt={medicine.name}
            className="w-full h-full object-cover rounded-xl"
          />
        </div>
        <div className="z-10 text-white flex-1">
          {medicine.featuredLabel && (
            <span className="bg-tertiary-fixed text-on-tertiary-fixed text-[9px] font-black px-2 py-0.5 rounded uppercase mb-2 inline-block">
              {medicine.featuredLabel}
            </span>
          )}
          <h4 className="text-2xl font-extrabold mb-1">{medicine.name}</h4>
          <p className="text-white/70 text-sm mb-4 max-w-sm">{medicine.featuredDescription || medicine.description}</p>
          <div className="flex items-center gap-6">
            <p className="text-2xl font-black">
              {medicine.price.toLocaleString()} <span className="text-sm font-medium">Kz</span>
            </p>
            <button
              onClick={() => onAdd?.(medicine.id)}
              className="px-6 py-2 bg-white text-primary font-bold rounded-xl text-sm hover:bg-blue-50 transition-colors"
            >
              Comprar Agora
            </button>
          </div>
        </div>
      </div>
    )
  }

  return (
    <div className={cn("bg-card p-5 rounded-2xl group hover:shadow-lg transition-all border border-border/5 flex gap-4", className)}>
      <div className="w-24 h-24 rounded-xl bg-muted overflow-hidden shrink-0">
        <img
          src={medicine.image}
          alt={medicine.name}
          className="w-full h-full object-cover mix-blend-multiply"
        />
      </div>
      <div className="flex flex-col justify-between flex-1">
        <div>
          <div className="flex justify-between items-start">
            <h4 className="font-bold text-foreground group-hover:text-primary transition-colors">
              {medicine.name}
            </h4>
            {medicine.inStock ? (
              <CheckCircle2 className="w-4 h-4 text-tertiary fill-tertiary" />
            ) : medicine.requiresPrescription ? (
              <Lock className="w-4 h-4 text-destructive" />
            ) : null}
          </div>
          <p className="text-xs text-muted-foreground">{medicine.description}</p>
        </div>
        <div className="flex justify-between items-end">
          <p className="text-lg font-black text-foreground">
            {medicine.price.toLocaleString()} <span className="text-xs font-medium">Kz</span>
          </p>
          <button
            onClick={() => onAdd?.(medicine.id)}
            disabled={medicine.requiresPrescription && !medicine.inStock}
            className={cn(
              "w-8 h-8 rounded-full flex items-center justify-center hover:scale-110 transition-transform",
              medicine.requiresPrescription
                ? "bg-muted text-muted-foreground"
                : "bg-primary/20 text-primary"
            )}
          >
            {medicine.requiresPrescription ? (
              <Lock className="w-4 h-4" />
            ) : (
              <Plus className="w-4 h-4" />
            )}
          </button>
        </div>
      </div>
    </div>
  )
}
