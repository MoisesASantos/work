"use client"

import Link from "next/link"
import { usePathname } from "next/navigation"
import { cn } from "@/lib/utils"
import { Search, Pill, MessageCircle, User } from "lucide-react"

const navItems = [
  { href: "/", label: "Explorar", icon: Search },
  { href: "/farmacias", label: "Saude", icon: Pill },
  { href: "/suporte", label: "Assistente", icon: MessageCircle },
  { href: "/perfil", label: "Perfil", icon: User },
]

export function BottomNav() {
  const pathname = usePathname()

  return (
    <nav className="fixed bottom-0 left-0 w-full z-50 flex justify-around items-center px-4 pb-6 pt-3 bg-white/90 dark:bg-slate-900/90 backdrop-blur-2xl rounded-t-3xl md:hidden shadow-[0_-4px_20px_rgba(0,0,0,0.05)]">
      {navItems.map((item) => {
        const isActive = pathname === item.href || 
          (item.href !== "/" && pathname.startsWith(item.href))
        const Icon = item.icon

        return (
          <Link
            key={item.href}
            href={item.href}
            className={cn(
              "flex flex-col items-center justify-center active:scale-90 transition-transform px-5 py-1.5 rounded-2xl",
              isActive
                ? "bg-blue-100 dark:bg-blue-900/40 text-blue-900 dark:text-blue-100"
                : "text-slate-400 dark:text-slate-500"
            )}
          >
            <Icon className="w-5 h-5" />
            <span className="text-[11px] font-medium">{item.label}</span>
          </Link>
        )
      })}
    </nav>
  )
}
