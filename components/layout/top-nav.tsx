"use client"

import Link from "next/link"
import { MapPin, Bell } from "lucide-react"
import Image from "next/image"

export function TopNav() {
  return (
    <header className="fixed top-0 right-0 left-0 md:left-64 z-40 bg-white/80 dark:bg-slate-900/80 backdrop-blur-xl border-b border-border/10 h-16 flex items-center justify-between px-4 md:px-6">
      {/* Logo - Mobile only */}
      <span className="text-xl font-bold tracking-tight text-primary font-serif md:hidden">
        Apothecary
      </span>

      {/* Location - Desktop */}
      <button className="hidden md:flex items-center gap-2 px-3 py-2 text-foreground hover:bg-muted transition-all rounded-xl">
        <MapPin className="w-5 h-5 text-primary" />
        <div className="text-left">
          <p className="text-sm font-semibold">Luanda, Angola</p>
          <p className="text-xs text-muted-foreground">Talatona</p>
        </div>
      </button>

      {/* Right Actions */}
      <div className="flex items-center gap-3">
        {/* Location - Mobile */}
        <button className="md:hidden p-2 text-foreground hover:bg-muted transition-all rounded-full flex items-center gap-2">
          <MapPin className="w-5 h-5 text-primary" />
        </button>

        {/* Notifications */}
        <button className="relative p-2.5 text-foreground hover:bg-muted transition-all rounded-full">
          <Bell className="w-5 h-5" />
          <span className="absolute top-1.5 right-1.5 w-2.5 h-2.5 bg-destructive rounded-full border-2 border-white" />
        </button>

        {/* Profile */}
        <Link href="/perfil" className="w-9 h-9 rounded-full bg-muted overflow-hidden ring-2 ring-primary/20 hover:ring-primary/40 transition-all">
          <Image
            src="https://images.unsplash.com/photo-1472099645785-5658abf4ff4e?w=100&h=100&fit=crop&crop=face"
            alt="Perfil do utilizador"
            width={36}
            height={36}
            className="w-full h-full object-cover"
          />
        </Link>
      </div>
    </header>
  )
}
